using UnityEngine;

public class Robotmovement : MonoBehaviour
{

    float speed = 10f;

    

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        float movement = Time.deltaTime * speed;

        if (Input.GetKey(KeyCode.H))
        {
            transform.Translate(new Vector3(-movement, 0, 0));
        }
        if(Input.GetKey(KeyCode.J))
        {
            transform.Translate(new Vector3(0, 0, movement));
        }
        if (Input.GetKey(KeyCode.K))
        {
            transform.Translate(new Vector3(0, 0, -movement));
        }
        if (Input.GetKey(KeyCode.L))
        {
            transform.Translate(new Vector3(movement, 0, 0));
        }



    }
}
