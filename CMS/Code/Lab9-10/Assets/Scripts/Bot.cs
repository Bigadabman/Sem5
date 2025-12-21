using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

public class Bot : MonoBehaviour
{

    float movespeed = 0.25f; // скорость передвижения танка-бота
    float rotspeedtank = 0.1f; // скорость поворота танка-бота
    float rotspeedbash = 0.5f; // скорость поворота башни танка-бота
    float speedcore = 3f;  // скорость снаряда танка-бота
    public Transform bash; // для управления башней
    public Transform stvol; // для управления стволом
    public GameObject core; // для ссылки на префаб снаряда
    bool canshoot = true; // для определения, может ли танк-бот произвести выстрел
    int life = 6;   // для определения максимального количества попаданий в танк-бот
  






    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.CompareTag("core"))
        {
     
            life--;

            if (life <= 0)
                Destroy(gameObject);
        }



    }





    // Start is called once before the first execution of Update after the MonoBehaviour is created
    Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
    }


    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerStay(Collider other)
    {


        if (other.tag == "Player")   // если бот попал в триггер танка-игрока выполняем
        {
            Vector3 relativePos = other.transform.position - transform.position;
            Quaternion newrot = Quaternion.LookRotation(relativePos);
            bash.rotation = Quaternion.Slerp(bash.rotation, newrot, Time.deltaTime * rotspeedbash);



            RaycastHit hit;
            //переменная для определения объекта попадания «луча»

            if (Physics.Raycast(bash.position, bash.TransformDirection(Vector3.forward), out hit))
            //если выпущен луч из башни в направлении относительно нее – вперед

            {
                if ((hit.transform.tag == "Player") && canshoot)
                    //если луч попал в коллайдер игрока и можно выстрелить
                    StartCoroutine(botshoot());
                //запускаем короутину для выстрела танка-бота
            }



            float distance = Vector3.Distance(other.transform.position, transform.position);

            if (distance < 20)
            {
                Vector3 forward = transform.forward * 1f;
                float angleToPlayer = Vector3.Angle(forward, relativePos);
                float angleThreshold = 20f;
                transform.rotation = Quaternion.Slerp(transform.rotation, newrot, Time.deltaTime * rotspeedtank);
                if (angleToPlayer < angleThreshold)
                {
                    transform.position = Vector3.Lerp(transform.position, other.transform.position, Time.deltaTime * movespeed);
                }
            }



        }

    }

    IEnumerator botshoot()
    {
        canshoot = false;       //указываем, что танк-бот стрелять пока не может

        //определяем координату для положения снаряда танка-бота 
        Vector3 forwardofstvol = stvol.transform.position + stvol.TransformDirection(Vector3.up * 4.5f);

        //создаем снаряд из префаба снаряда в требуемой координате относительно ствола
        GameObject newcore = Instantiate(core, forwardofstvol, stvol.rotation);

        gameObject.GetComponent<AudioSource>().PlayOneShot(gameObject.GetComponent<AudioSource>().clip);




        yield return new WaitForSeconds(3f);        //ждем 3 секунды (время «перезарядки»)

        canshoot = true;        //указываем, что танк может сделать выстрел
    }




}
