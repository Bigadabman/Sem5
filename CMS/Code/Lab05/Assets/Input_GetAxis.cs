using UnityEngine;

public class Input_GetAxis : MonoBehaviour
{

    float verticalAngle;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        float z = Input.GetAxis("Vertical");
        float x = Input.GetAxis("Horizontal");
        transform.Translate(x, 0, z);

        float y = Input.GetAxis("Mouse Y");
        float x1 = Input.GetAxis("Mouse X");
        //transform.Rotate(x1, y, 0);

        verticalAngle += y;
        verticalAngle = Mathf.Clamp(verticalAngle, 0f, 90f);

        transform.localRotation = Quaternion.Euler(verticalAngle, transform.localEulerAngles.y - x1, 0f);
    }
}
