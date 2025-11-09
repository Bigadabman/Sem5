using UnityEngine;

public class blueLightOnOff : MonoBehaviour
{


    public Light[] blueLights;


    public int lightIntensity = 500;

    private void OnTriggerEnter(Collider other)
    {

        if (other.name == "body")
        {
            foreach (Light light in blueLights)
            {
                light.intensity = lightIntensity;
            }

        }
    }


    private void OnTriggerExit(Collider other)
    {
        if (other.name == "body")
        {
            foreach (Light light in blueLights)
            {
                light.intensity = 0;
            }
        }
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
