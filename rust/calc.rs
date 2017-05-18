
use std::io;

fn main () {
    let mut accumulator = 0;
    println!("My name is Jonas");   

    let mut input = String::new();
    loop {
        println!("Action : +,-,*,/");        
        match io::stdin().read_line(&mut input) {
            Ok(n) => {},
            Err(error) => {},
        }
        accumulator += 1;
        match &input as &str  {
            "+" => jet::add(),
            "-" => jet::sub(),
            "*" => jet::mul(),
            "/" => jet::div(),
            "%" => jet::modulus(),
            _   => println!("Default... {}", input),
        }
        break;
    }
}

mod jet {
    pub fn add() {
        println!("computing '+' ")
    }

    pub fn sub() {
        println!("computing '-' ")
    }

    pub fn mul() {
        println!("computing '*' ")
    }

    pub fn div() {
        println!("computing '/' ")
    }

    pub fn modulus() {
        println!("computing '%' ")
    }
}
