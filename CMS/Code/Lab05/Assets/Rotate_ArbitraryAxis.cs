using UnityEngine;

public class Rotate_ArbitraryAxis : MonoBehaviour
{

    public float speed = 90f;

    public float angle = 0f;

    public Vector3 axis = new Vector3(1f, 1f, 0f);

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

       axis.Normalize();

    }

    // Update is called once per frame
    void Update()
    {
        angle += speed * Time.deltaTime;
        transform.rotation = Quaternion.AngleAxis(angle, axis);

    }
}
