using UnityEngine;

public class Party : MonoBehaviour
{

    public Light Light1;
    public Light Light2;
    public Light Light3;

    public GameObject cylynder;


    private void OnTriggerStay(Collider other)
    {
        if(other.name == "Player")
        {
            if (Light1.intensity < 10) Light1.intensity += 0.01f;
            else Light1.intensity = 0;

            if (Light2.intensity < 10) Light2.intensity += 0.01f;
            else Light2.intensity = 0;

            if (Light3.intensity < 10) Light3.intensity += 0.01f;
            else Light3.intensity = 0;

            cylynder.transform.Rotate(0, 1, 0);

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
