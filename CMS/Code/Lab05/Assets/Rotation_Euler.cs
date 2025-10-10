using UnityEngine;

public class Rotation_Euler : MonoBehaviour
{
    public float speedX = 90f;
    public float speedZ = 60f;

    public float angleX;
    public float angleZ;

    // Update is called once per frame
    void Update()
    {
        angleX += speedX * Time.deltaTime;
        angleZ += speedZ * Time.deltaTime;

        transform.eulerAngles = new Vector3(angleX, 0f, angleZ);
    }
}
