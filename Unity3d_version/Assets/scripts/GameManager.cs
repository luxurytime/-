using UnityEngine;
using System.Collections;


public class GameManager : MonoBehaviour {

	public static GameManager Instance;
	public int m_score = 0;

	public AudioClip m_musicClip;

	public Transform m_explosionFX;

	protected Player m_player;
	protected AudioSource m_audio;

	void Awake()
	{
		Instance = this;
		Debug.Log (Screen.width + "__" + Screen.height);
	}

	// Use this for initialization
	void Start () 
	{
		m_audio = this.audio;
		GameObject obj = GameObject.FindGameObjectWithTag ("Player");
		if( obj )
		{
			m_player = obj.GetComponent<Player>();
		}
	}
	
	// Update is called once per frame
	void Update () 
	{
		if( !m_audio.isPlaying )
		{
			m_audio.clip = m_musicClip;
			m_audio.Play();
		}

		if( Time.timeScale > 0 && Input.GetKeyDown( KeyCode.Escape ) )
		{
			Time.timeScale = 0;
		}
	}

	void OnGUI()
	{
		if( Time.timeScale == 0 )
		{
			if( GUI.Button( new Rect( Screen.width * 0.5f - 50, Screen.height * 0.4f, 100, 50 ), "Continue" ) )
			{
				Time.timeScale = 1;
			}
		}

		int life = 0;
		life = (int)m_player.m_life;
		/*if( m_player )
		{
			life = (int)m_player.m_life;
		}
		else
		{
			GUI.skin.label.fontSize = 50;

			GUI.skin.label.alignment = TextAnchor.LowerCenter;
			GUI.Label( new Rect( 0, Screen.height * 0.2f, Screen.width, 60 ), "You Lose" );

			GUI.skin.label.fontSize = 20;

			if( GUI.Button( new Rect( Screen.width * 0.5f - 50, Screen.height * 0.5f, 100, 50 ), "Again?" ) )
			{
				Application.LoadLevel( Application.loadedLevelName );
			}
		}*/
		if (m_score >= 100) {
			m_player.m_life++;
			m_score -= 100;
		}

		if (m_score < 0) {
			Destroy(m_player);

			GUI.skin.label.fontSize = 30;
			
			GUI.skin.label.alignment = TextAnchor.LowerCenter;
			GUI.Label( new Rect( 0, Screen.height * 0.2f, Screen.width, 40 ), "You Lose" );
			GUI.skin.label.fontSize = 20;
			GUI.Label( new Rect( 0, Screen.height * 0.2f, Screen.width, 80 ), "Hint:Try to reach 9 life" );
			GUI.skin.label.fontSize = 10;
			GUI.Label( new Rect( 0, Screen.height * 0.2f, Screen.width, 100 ), "子弹消灭敌人score+10,score超过100清零且life+1,撞毁敌人life-1,敌人到达底部score-10" );
			GUI.skin.label.fontSize = 20;
			
			if( GUI.Button( new Rect( Screen.width * 0.5f - 50, Screen.height * 0.5f, 100, 50 ), "Again?" ) )
			{
				Application.LoadLevel( Application.loadedLevelName );
			}

		}

		if (m_player.m_life > 9) {
			Destroy(m_player);
			
			GUI.skin.label.fontSize = 50;
			
			GUI.skin.label.alignment = TextAnchor.LowerCenter;
			GUI.Label( new Rect( 0, Screen.height * 0.2f, Screen.width, 60 ), "You Win" );
			/*GUI.skin.label.fontSize = 20;
			GUI.Label( new Rect( 0, Screen.height * 0.2f, Screen.width, 80 ), "Hint:" );*/
			GUI.skin.label.fontSize = 20;
			
			if( GUI.Button( new Rect( Screen.width * 0.5f - 50, Screen.height * 0.5f, 100, 50 ), "Again?" ) )
			{
				Application.LoadLevel( Application.loadedLevelName );
			}
			
		}

		GUI.skin.label.fontSize = 15;
		
		GUI.Label( new Rect( 5, 5, 100, 30 ), "Life：" + life );
		
		GUI.skin.label.alignment = TextAnchor.LowerCenter;

		GUI.Label(new Rect (0, 5, Screen.width, 30), "score：" + m_score);
	}

	public void AddScore( int p )
	{
		if (m_score < 0 || m_player.m_life > 9) return;
		m_score += p;
	}

}










