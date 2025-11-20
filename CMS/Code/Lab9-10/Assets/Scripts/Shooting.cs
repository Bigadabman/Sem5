using UnityEngine;

public class Shooting : MonoBehaviour
{

    public GameObject core;


    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            Vector3 forwardofstvol = transform.position +
            transform.TransformDirection(Vector3.up * 4.5f);
            GameObject newcore = Instantiate(core, forwardofstvol, transform.rotation);

            gameObject.GetComponent<AudioSource>().PlayOneShot(gameObject.GetComponent<AudioSource>().clip);

        }



    }
}
