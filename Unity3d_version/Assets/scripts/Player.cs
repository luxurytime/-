using UnityEngine;
using System.Collections;
//[AddComponentMenu("MyGame/Player")]

public class Player : MonoBehaviour {

	public float m_speed = 10.0f;
	public float m_life = 3;
	public Transform m_rocket;
	public AudioClip m_shootClip;
	public Transform m_explosionFX;

	protected AudioSource m_audio;

	protected Transform m_transform;


	float m_rocketRate = 0;
	// Use this for initialization
	void Start () 
	{
		m_transform = this.transform;
		m_audio = this.audio;
	}
	
	// Update is called once per frame
	void Update () 
	{
		float moveV = 0;
		float moveH = 0;



		if (Input.GetKey (KeyCode.UpArrow) || Input.GetKey( KeyCode.W ) ) 
		{
			moveV -= m_speed * Time.deltaTime;
		}
		if (Input.GetKey (KeyCode.DownArrow) || Input.GetKey( KeyCode.S ) ) 
		{
			moveV += m_speed * Time.deltaTime;
		}
		if (Input.GetKey (KeyCode.LeftArrow) || Input.GetKey( KeyCode.A ) ) 
		{
			moveH += m_speed * Time.deltaTime;
		}
		if (Input.GetKey (KeyCode.RightArrow) || Input.GetKey( KeyCode.D ) ) 
		{
			moveH -= m_speed * Time.deltaTime;
		}

		moveV -= Input.acceleration.y * m_speed / 10 ;
		moveH -= Input.acceleration.x * m_speed / 10 ;

		this.m_transform.Translate (new Vector3 ( moveH, 0, moveV ));

		float kV = 0;
		float kH = 0;

		if (this.m_transform.position.x < -7.5f)
		{
			kV = this.m_transform.position.x + 7.5f;

		}
		else if( this.m_transform.position.x > 7.5f )
		{
			kV = this.m_transform.position.x - 7.5f;
		}
		if (this.m_transform.position.z < -4.2f)
		{
			kH = this.m_transform.position.z + 4.2f;
		}
		else if( this.m_transform.position.z > 4.2f )
		{
			kH = this.m_transform.position.z - 4.2f;
		}
		this.m_transform.Translate (new Vector3 ( kV, 0, kH));



		m_rocketRate += Time.deltaTime;
		if (m_rocketRate > 0.1f) 
		{
			m_rocketRate = 0;
			if (Input.GetKey (KeyCode.Space) || Input.GetMouseButton (0)) 
			{
				Instantiate( m_rocket, m_transform.position, m_transform.rotation );
				m_audio.PlayOneShot(m_shootClip);
			}
		}
	}

	void OnTriggerEnter( Collider col )
	{
		if( col.tag != "PlayerRocket" )
		{
			m_life -= 1;
		}
		/*if( m_life <= 0 )
		{
			Instantiate( m_explosionFX, m_transform.position, Quaternion.identity );
			Destroy( this.gameObject );
		}*/
	}
	
	

}












