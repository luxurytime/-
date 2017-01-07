using UnityEngine;
using System.Collections;

public class Enemy : MonoBehaviour {

	public float m_speed = 4;
	public float m_life = 1;
	public Transform m_explosionFX;
	public int m_point = 10;

	protected float m_rotSpeed = 30;
	protected float m_timer = 1.5f;
	protected Transform m_transform;

	// Use this for initialization
	void Start () 
	{
		m_transform = this.transform;
	}
	
	// Update is called once per frame
	void Update () 
	{
		float random_speed = Random.Range (-3.0f, -1.0f);
		UpdateMove (random_speed);
	}

	protected virtual void UpdateMove(float speed)
	{
		m_timer -= Time.deltaTime;
		if( m_timer <= 0 )
		{
			m_timer = 3;
			m_rotSpeed = -m_rotSpeed;
		}
		float random_speed = m_speed * Random.value;
		//m_transform.Rotate (Vector3.up, m_rotSpeed * Time.deltaTime, Space.World);
		m_transform.Translate( new Vector3( 0, 0, speed * Time.deltaTime ) );

	}

	void OnTriggerEnter( Collider other )
	{
		if( other.tag.CompareTo("PlayerRocket") == 0 )
		{
			Rocket rocket = other.GetComponent<Rocket>();
			if( rocket != null)
			{
				m_life -= rocket.m_power;
				GameManager.Instance.AddScore( m_point );
				beHit();
			}
		}
		else if( other.tag.CompareTo("Player") == 0 )
		{
			beHit();
		}

		if( other.tag == "bound" )
		{
			m_life = 0;
			GameManager.Instance.AddScore( -10 );
			Destroy( this.gameObject );
		}
	}

	void beHit()
	{
		m_life = 0;
		Instantiate( m_explosionFX, m_transform.position, Quaternion.identity );
		Destroy( this.gameObject );
	}


}








