using UnityEngine;

public class Rotation_Qaternion : MonoBehaviour
{

    public Quaternion orig;

    public float speedX = 90f;
    public float speedZ = 60f;

    public float angleX;
    public float angleZ;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        orig = transform.rotation;
    }

    // Update is called once per frame
    void Update()
    {
        angleX += speedX * Time.deltaTime;
        angleZ += speedZ * Time.deltaTime;

        Quaternion rotX = Quaternion.AngleAxis(angleX, Vector3.right);
        Quaternion rotZ = Quaternion.AngleAxis(angleZ, Vector3.forward);

        transform.rotation = orig * rotX * rotZ;

    }
}
