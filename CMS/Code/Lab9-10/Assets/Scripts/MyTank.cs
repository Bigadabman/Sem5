using UnityEngine;

public class mytank : MonoBehaviour
{

    public GameObject bomb;

    public float spawnHeight = 20f; // ¬ысота, с которой падают бомбы
    public float areaSize = 10f; // –азмер зоны падени

    //Vector3 startPositon = new Vector3(80, 2, 70);
    //Quaternion startRotation = new Quaternion(0, 0, 0, 0);

    Transform bash;			//- объектна€ переменна€ дл€ управлени€ башней
    Transform stv; 			//- объектна€ переменна€ дл€ управлени€ стволом
    int TankMoveSpeed = 20;// - дл€ регулировани€ скорости движени€ танка
    float RotateSpeed = 0.5f; 	// - дл€ регулировани€ скорости вращени€ башни

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
