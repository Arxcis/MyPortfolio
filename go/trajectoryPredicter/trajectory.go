package main
import "fmt"
import "math"
import "os"
import "strconv"

type Vector struct {
    x float64
    y float64
    z float64
}

func Add(a Vector, b Vector) Vector {
    return Vector{a.x + b.x, a.y + b.y, a.z + b.z}
}

func Sub(a Vector, b Vector) Vector {
    return Vector{ a.x - b.x, a.y - b.y, a.z - b.z}
}

func Mul(a Vector, factor float64) Vector {
    return Vector{ a.x * factor, a.y * factor, a.z * factor}
}

func Len(a Vector) float64 {
    return math.Sqrt(a.x*a.x + a.y*a.y + a.z*a.z)
}

func Lexrp(a Vector, b Vector, t float64) Vector {
    return Add(b, Mul( Sub(a, b), t))
}

//
// @function pedictLaunchVelocity
//   @brief predicts launch speed velocity to hit a target based on linear extrapolation of 
//     targets trajectory. Solves the problem iterating many timesteps, until the right trajectory
//     is found.
//     - Assuming the target is in a space where the projectile starts at {0,0}
//     - Assuming the canon only fires between 0 and 90 degrees or pi/2 radians
//     - Assuming no wind resistance
//     - Assuming negative gravity (positive might work but is untested)
//
func PredictLaunchVelocity(target0 Vector,  
                           target  Vector,
                           speed   float64, 
                           gravity float64, 
                           sign    float64) Vector {    

    const timestep       float64 = 0.1
    var targetTime       float64 = 0.0
    var projectileTime   float64 = 999.0
    var launchVelocity2D Vector
    var target2D         Vector

    for projectileTime - targetTime > timestep {
        // ---- 1. Predict where the target would be in the future 
        {
            var temp = target
            target   = Lexrp(target0, target, timestep)
            target0  = temp
            targetTime += timestep
        }

        // ---- 2. Calculate targetPosition from base in vertical 2D space 
        {
            var targetXZ = Vector { target.x, target.z, 0.0 }
            target2D     = Vector {
                x: Len(targetXZ),
                y: target.y,
                z: 0.0,
            }   
        }

        // ---- 3. Compute launch velocity to hit the target(t) 
        //          Using formula of trajectory of projectile from Wikipedia 
        {
            var coeffisient = (gravity * target2D.x * target2D.x) / (2 * speed * speed)
            var sqrtVar     = (target2D.x * target2D.x) - (4 * coeffisient * (coeffisient - target2D.y))

            if sqrtVar >= 0 {
                var angle        = math.Atan((-target2D.x + (sign) * math.Sqrt(sqrtVar)) / (2 * coeffisient))
                launchVelocity2D = Vector { 
                    x: speed * math.Cos(angle), 
                    y: speed * math.Sin(angle), 
                    z: 0,
                }

            } else {
                //fmt.Println("Target out of reach....!\n")
                return Vector{0,0,0}
            }
        }

        // ---- 4. Compute the time it takes for projectile to hit target
        projectileTime = target2D.x / launchVelocity2D.x
    }

    // ---- 5. Valid trajectory found, transform 2D vector back to 3D space
    var angleXZ = math.Atan2(target.z, target.x)
    return Vector {
        x: launchVelocity2D.x * math.Cos(angleXZ),
        y: launchVelocity2D.y,
        z: launchVelocity2D.x * math.Sin(angleXZ),
    }
}

func main() {

    var launchSpeed float64
    var gravity     float64 = -10.0

    // ---- 1. Parse command-line args
    {
        args := os.Args[1:]
        if len(args) >= 1 { 
            launchSpeed, _ = strconv.ParseFloat(args[0], 64)
        } else {              
            launchSpeed = 50.0
        }
    }

    // ---- 2. Find launch vectors for various launchSpeeds
    {
        var target0 = Vector {0, 0, 10.0}
        var target  = Vector {0, 30, 20.0}
        
        for i := 0; i < 30; i++ {
            fmt.Println(
                "LaunchSpeed: ", launchSpeed, 
                "     Result: ", PredictLaunchVelocity(target0, target, launchSpeed, gravity, 1))
            launchSpeed += 1.0
        }
    }
}