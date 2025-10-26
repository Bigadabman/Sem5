using UnityEngine;

public class PlayerMove : MonoBehaviour
{
    float speed = 10f;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        float vertical = Input.GetAxis("Vertical");
        float horizontal = Input.GetAxis("Horizontal");
        Vector3 movement = new Vector3(Time.deltaTime * speed * horizontal, 0, Time.deltaTime * speed * vertical);
        transform.Translate(movement);

        float MouseX = Input.GetAxis("Mouse X");

        transform.Rotate(new Vector3(0, MouseX, 0));


    }
}
