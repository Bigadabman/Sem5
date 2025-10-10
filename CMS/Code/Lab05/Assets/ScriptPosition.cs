using UnityEngine;

public class ScriptPosition : MonoBehaviour
{
    Vector3 movement = new Vector3(0.01f, 0.02f, -0.02f);

    // Update is called once per frame
    void Update()
    {
        transform.position += movement;
        
    }
}
