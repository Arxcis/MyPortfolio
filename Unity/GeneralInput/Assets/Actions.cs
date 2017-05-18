using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class Actions : MonoBehaviour {

	// Public
	public enum Device : int {		// Used to access correct slot in string[] device names
		Keyboard1,
		Keyboard2,
		Joy1,
		Joy2,
		Joy3,
		Joy4
	};

	public bool keyboardOn = false;													  // On/off keyboard 1 and 2
	public List<Device> activeDevices = new List<Device>();   // Maps players to their respective device.

	// Private
	string[] DeviceNames = {				// Names that works as keys to access the Input.GetAxis(name+axis)
		"Keyboard1",
		"Keyboard2",
		"Joy1",
		"Joy2",
		"Joy3",
		"Joy4",
	};

	Vector2 moveInput  = Vector2.zero;							// Stores temp values for all the input axes
	Vector2 aimInput   = Vector2.zero;
	Vector3 mouseInput = Vector3.zero;
	float   fireInput  = 0.0F;


	// Use this for initialization
	void Start ()
	{
		MapActiveDevices();           // Sets up each player with an active input device
	}

	void FixedUpdate ()
	{
		CallActions();
	}

	void MapActiveDevices()
	{
		int i = (keyboardOn) ? 0 : 2;													// Maps players to a input device
		foreach (GameObject players in Main.Players()) {		  //
			activeDevices.Add( (Device)i );   									// Cast to enum
			i++;
		}
	}

	void CallActions()
	{
		int i = 0;
				// Actions setup!
	  foreach (GameObject player in Main.Players())
		{

			// -------------------- Move ------------------------
			moveInput.x = Input.GetAxisRaw( DeviceNames[ (int)activeDevices[i] ] + "_MoveHorizontal");
			moveInput.y = Input.GetAxisRaw( DeviceNames[ (int)activeDevices[i] ] + "_MoveVertical"  );

			// Main.Player<MovePlayer>(i).Move( moveInput );

			Debug.Log( DeviceNames[ (int)activeDevices[i] ] + "_Move" + moveInput);

			// --------------------- Aim --------------------------
			if( activeDevices[i] == Device.Keyboard1 ) {
				mouseInput = Input.mousePosition;
				// Main.Player<GunScript>(i, "Gun").mouseAimUpdate( Input.mousePosition );
				// Debug.Log(DeviceNames[ (int)activeDevices[i] ] + "_Mouse" + mouseInput);
			}
			else
			{
			  aimInput.x = Input.GetAxisRaw( DeviceNames[ (int)activeDevices[i] ] + "_AimHorizontal");
			  aimInput.y = Input.GetAxisRaw( DeviceNames[ (int)activeDevices[i] ] + "_AimVertical"  );

			  // Main.Player<GunScript>(i, "Gun").keyAimUpdate( aimInput );

				Debug.Log( DeviceNames[ (int)activeDevices[i] ] + "_Aim" + aimInput);
			}


			// --------------------- Fire ------------------------------
			fireInput = Input.GetAxisRaw( DeviceNames[ (int)activeDevices[i] ] + "_Fire" );
			// Main.Player<GunScript>(i, "Gun").fire( fireInput );

			if( fireInput > 0.4) Debug.Log( DeviceNames[ (int)activeDevices[i] ] + "_Fire" + fireInput);
			i++;
		}
	}
	// End of class
}


// void OnValidate() {
//
// 	List<Device> tempDevices = new List<Device>();
//
// 	if(activeDevices.Length <= 5) {
// 		for(int i=0; i<activeDevices.Length; i++ ) {
//
// 			if(!tempDevices.Contains((Device)i)) {
// 				tempDevices.Add((Device)i);
// 			}
// 		}
// 		activeDevices = tempDevices.ToArray();
// 	}
// }
