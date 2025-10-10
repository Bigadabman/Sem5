using UnityEngine;

public class Move_Key : MonoBehaviour
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKey(KeyCode.A))
        {
            transform.position += new Vector3(-0.1f, 0, 0);
        }

        if (Input.GetKey(KeyCode.D))
        {
            transform.position += new Vector3(0.1f, 0, 0);
        }

        if (Input.GetKey(KeyCode.W))
        {
            transform.position += new Vector3(0, 0.1f, 0);
        }

        if (Input.GetKey(KeyCode.S))
        {
            transform.position += new Vector3(0, -0.1f, 0);
        }

        if (Input.GetKey(KeyCode.Q))
        {
            transform.position += new Vector3(0, 0, -0.1f);
        }

        if (Input.GetKey(KeyCode.E))
        {
            transform.position += new Vector3(0, 0, 0.1f);
        }




    }
}
