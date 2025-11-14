using UnityEngine;

public class OpenTheDoor : MonoBehaviour
{

    public GameObject Vint;


    public GameObject stavn;
    public GameObject stavn1;

    private void OnTriggerEnter(Collider other)
    {
        if (other.name == "Player")
        {
            stavn.transform.position += new Vector3(-0.75f, 0, 0);
            stavn1.transform.position += new Vector3(0.75f, 0, 0);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if(other.name == "Player")
        {
            stavn.transform.position -= new Vector3(-0.75f, 0, 0);
            stavn1.transform.position -= new Vector3(0.75f, 0, 0);
        }

    }


    private void OnTriggerStay(Collider other)
    {
        if(other.name == "Robot")
        {
            Vint.transform.Translate(0.1f, 0, 0);
            Vint.transform.Rotate(0, 3, 0);
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
