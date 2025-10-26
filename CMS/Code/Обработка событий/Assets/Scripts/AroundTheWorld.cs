using UnityEngine;

public class AroundTheWorld : MonoBehaviour
{

    public Light SpotLight;

    private void OnTriggerStay(Collider other)
    {
        if (other.name == "Player")
            SpotLight.transform.Rotate(0,3,0);
    }


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
