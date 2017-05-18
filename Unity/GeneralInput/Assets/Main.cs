using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class Main : MonoBehaviour {




	// NEW PLAYER SYSTEM
	static List<GameObject> players = new List<GameObject>();    // An array with pointers to all the active players.
	static GameObject selectedPlayer;                            // Selected player at any given moment

	void Awake ()
	{
		if( GameObject.FindGameObjectsWithTag("Player").Length < 1 ) { Debug.Log("NO PLAYERS FOUND IN SCENE!"); }  // Important check

		foreach (GameObject playerObject in GameObject.FindGameObjectsWithTag("Player")) {
			players.Add(playerObject);                   // Finds all GameObjects tagged 'player' in given scene
		};

	}

	// Update is called once per frame
	void Update () {

	}

	/* GENERAL PLAYER INTERFACE FUNCTIONS
     * Description: Overriding the Player-function to support returning multiple types:
     *                0. Players()                   -> List<GameObject>
     *                1. Player(index)               -> GameObject
     *                2. Player(index, childname)    -> GameObject
     *                3. Player<component>(index)    -> Component
     *                4. Player<component>(index, childname) -> Component
    */
	public static List <GameObject> Players()
	{
		return players;
	}

	public static GameObject Player(int playerIndex)
	{
		return players[playerIndex];
	}

	public static GameObject Player(int playerIndex, string child)
	{

		return players[playerIndex]
			.transform
				.Find(child)
					.gameObject;
	}

	public static T Player<T>(int playerIndex) where T : Component
	{
		return players[playerIndex]
			.GetComponent<T>();
	}

	public static T Player<T>(int playerIndex, string child) where T : Component
	{
		return players[playerIndex]
			.transform
			  .Find(child)
			    .gameObject
					  .GetComponent<T>();
	}





	// --------------- UTILITY FUNCTIONS ------------------

	// Takes a Vector2 which has a variable absolute length
	// between 1 at 90 degrees, and sqrt(2) at 45 degrees
	// Returns a Vector2 which has an absolute length of 1
	// for all angles.
	public static Vector2 DiagonalCompensate( Vector2 inVec )
	{                                    // Gets angle and converts it to radians
		float angle = GetAngle( Vector2.right, inVec) * Mathf.Deg2Rad;

		return new Vector2( inVec.x * Mathf.Abs(Mathf.Cos(angle)),
			inVec.y * Mathf.Abs(Mathf.Sin(angle)) );
	}

	// Returns the correct angle between two vectors
	public static float GetAngle( Vector2 v1, Vector2 v2 )
	{
		float sign = Mathf.Sign( v1.x * v2.y - v1.y * v2.x );
		return Vector2.Angle(v1, v2) * sign;
	}

	// Returns a unit vector given a specific angle
	public static Vector2 GetUnitVector2(float angle)
	{
		return new Vector2( Mathf.Cos(angle), Mathf.Sin(angle) );
	}

	// Casts a Vector2 to a Vector3
	public static Vector3 ToVector3( Vector2 vec2, float zval=0.0F )
	{
		return new Vector3(vec2.x, vec2.y, zval);
	}

	public static float pitchDeviation (float range)       //used to give a deviation in pitch when playing a sound. normal value is 0.1f:
	{
		return 1f + Random.Range(-range, range);    //meaning that the pich can go from 0.90f t0 1.10f.
	}
}
