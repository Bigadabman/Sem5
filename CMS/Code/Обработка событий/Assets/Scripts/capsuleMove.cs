using Unity.Mathematics;
using UnityEngine;
using UnityEngine.EventSystems;
public class capsuleMove : MonoBehaviour
{

    public Texture2D[] textures;

    public GameObject Cube1;
    public GameObject Cube2;

    System.Random random = new System.Random();


    void randomChangeTexture(GameObject obj)
    {
        obj.gameObject.GetComponent<Renderer>().material.mainTexture = textures[random.Next(3)];
    }

    public void OnCollisionEnter(Collision col)
    {
        //float red = Random.Range(.0f, 1.0f);
        //float green = Random.Range(.0f, 1.0f);
        //float blue = Random.Range(.0f, 1.0f);
        //Color col1 = new Color(red, green, blue);
        //col.gameObject.GetComponent<Renderer>().material.color = col1;

        


        randomChangeTexture(col.gameObject);
      
    }


   



    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float z = Input.GetAxis("Vertical");
        float x = Input.GetAxis("Horizontal");

        transform.Translate(x/20, 0, z/20);


        float mouseX = Input.GetAxis("Mouse X");
        transform.Rotate(0,mouseX,0);


        if (Input.GetKeyDown(KeyCode.Alpha1))
        {
            randomChangeTexture(Cube1);
        }

        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            randomChangeTexture(Cube2);
        }


        
    }
}
