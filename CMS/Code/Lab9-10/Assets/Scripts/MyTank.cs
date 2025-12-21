using UnityEngine;

public class mytank : MonoBehaviour
{

    public GameObject bomb;

    public float spawnHeight = 20f; // Высота, с которой падают бомбы
    public float areaSize = 10f; // Размер зоны падени

    //Vector3 startPositon = new Vector3(80, 2, 70);
    //Quaternion startRotation = new Quaternion(0, 0, 0, 0);

    Transform bash;			//- объектная переменная для управления башней
    Transform stv; 			//- объектная переменная для управления стволом
    float TankMoveSpeed = 20f;// - для регулирования скорости движения танка
    float RotateSpeed = 0.5f; 	// - для регулирования скорости вращения башни




    AudioSource source_tank;
    bool isPlaying = false;


    void Start()
    {
        source_tank = GetComponent<AudioSource>();

        areaSize = gameObject.GetComponent<Renderer>().bounds.size.z;

        bash = gameObject.transform.Find("head");
        stv = bash.transform.Find("gun");
    }



    // Update is called once per frame
    void Update()
    {

        /*
        if (transform.position.y < -10)
        {
            transform.position = startPositon;
            transform.rotation = new Quaternion(0, 0, 0, 0);
        }
        if (transform.rotation.x == 180)
        {
            transform.position += new Vector3(0, 3, 0);
            transform.Rotate(180, 0, 0);
        }
        */

            


        float speed = TankMoveSpeed * Time.deltaTime;


        float z = Input.GetAxis("Vertical");         // клавиши W и S
        transform.Translate(0, 0, z * speed);                       // движение вперед-назад

        float x = Input.GetAxis("Horizontal");      // клавиши A и D
        transform.Rotate(0f, x * RotateSpeed, 0f);                // повороты танка

        float h = Input.GetAxis("Mouse X");
        bash.Rotate(0f, h , 0f);      // поворот башни

        float v = Input.GetAxis("Mouse Y");
        // ось Z направлена горизонтально
        stv.transform.Rotate(-v, 0, 0);



        if((x!=0 || z!=0) && !isPlaying)
        {
            isPlaying = true;
            source_tank.Play();
        }
        if((x==0 && z == 0) && isPlaying)
        {
            isPlaying= false;
            source_tank.Stop();
        }




        if(Input.GetKeyDown(KeyCode.Space))
        {

            SpawnBombs(5);

        }



    }


    private float h = -170;
    void OnGUI()
    {
        GUI.BeginGroup(new Rect(10, h, 250, 300));
        GUI.Box(new Rect(10, 0, 200, 200), "УПРАВЛЕНИЕ СКОРОСТЬЮ");
        GUI.Label(new Rect(15, 30, 200, 30), "Скорость танка  " + TankMoveSpeed + "  ");
        TankMoveSpeed = GUI.HorizontalSlider(new Rect(15, 50, 170, 30), TankMoveSpeed, 0.0f, 20.0f);
        if (GUI.Button(new Rect(10, 170, 90, 20), "Скрыть ПУ")) { Hide(); }
        if (GUI.Button(new Rect(100, 170, 90, 20), "Показать ПУ")) { Show(); }
        GUI.EndGroup();
    }
    public void Hide() { h = -170; }
    public void Show() { h = 0; }





    void SpawnBombs(int count)
    {
        
        Vector3 center = transform.position + transform.forward * 10f;

        for (int i = 0; i < count; i++)
        {
            
            float offsetX = Random.Range(-areaSize, areaSize);
            float offsetZ = Random.Range(-areaSize, areaSize);

            Vector3 spawnPos = new Vector3(center.x + offsetX, spawnHeight, center.z + offsetZ);

            
            Instantiate(bomb, spawnPos, Quaternion.identity);
        }
    }



}
