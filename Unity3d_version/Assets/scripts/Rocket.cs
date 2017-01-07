using UnityEngine;
using System.Collections;
[AddComponentMenu("MyGame/Rocket")]
public class Rocket : MonoBehaviour {

	//子弹飞行速度
	public float m_speed = 10;
	//生存时间
	public float m_liveTime = 1;
	//子威力
	public float m_power = 1.0f;
	protected Transform m_transform;



	// Use this for initialization
	void Start () 
	{
		m_transform = this.transform;
	}
	
	// Update is called once per frame
	void Update () 
	{
		m_liveTime -= Time.deltaTime;
		if (m_liveTime <= 0) 
		{
			Destroy(this.gameObject);
		}
		m_transform.Translate( new Vector3( 0, 0, -m_speed * Time.deltaTime ) );
	}

	void OnTriggerEnter( Collider col )
	{
		if( col.tag != "Enemy" )
			return;

		Destroy (this.gameObject);
	}

}







