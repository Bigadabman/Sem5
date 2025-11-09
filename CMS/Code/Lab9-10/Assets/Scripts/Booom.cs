using UnityEditor.SceneManagement;
using UnityEngine;



public class Booom : MonoBehaviour
{
    AudioSource boomBox;

    

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {

        boomBox = GetComponent<AudioSource>();
        
    }

    // Update is called once per frame
    void Update()
    {

        float objectheight = GetComponent<Renderer>().bounds.size.y / 2;

        if (gameObject.transform.position.y <= objectheight)
        {
            gameObject.GetComponent<Rigidbody>().useGravity = false;
            gameObject.GetComponent<Collider>().enabled = false;
            gameObject.GetComponent<MeshRenderer>().enabled = false;
            boomBox.PlayOneShot(gameObject.GetComponent<AudioSource>().clip);



            Destroy(gameObject, boomBox.clip.length);
        }
    }
}
