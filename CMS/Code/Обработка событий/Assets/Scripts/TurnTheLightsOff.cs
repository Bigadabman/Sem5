using UnityEngine;

public class TurnTheLightsOff : MonoBehaviour
{
    public Light pointLight;

    private void OnTriggerEnter(Collider other)
    {
        if (other.name == "Player")
            pointLight.enabled = true;
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.name == "Player")
            pointLight.enabled = false;
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
