using JetBrains.Annotations;
using UnityEngine;

public class CubeGenerator : MonoBehaviour
{

    public float minX; public float maxX;
    public float minZ; public float maxZ;

    public float nX; public float nY; public float nZ;

    public GameObject prefub1;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        MeshRenderer rend = gameObject.GetComponent<MeshRenderer>();

        minX = rend.bounds.min.x; maxX = rend.bounds.max.x;
        minZ = rend.bounds.min.z; maxZ = rend.bounds.max.z;

        nY = gameObject.transform.position.y+5;
        

    }

    // Update is called once per frame
    void Update()
    {
        nX = Random.Range(minX, maxX);
        nZ = Random.Range(minZ, maxZ);

        if (Input.GetKey(KeyCode.Q))
        {
            GameObject cub = GameObject.CreatePrimitive(PrimitiveType.Cube);
            cub.transform.position= new Vector3(nX, nY, nZ);
            cub.AddComponent<Rigidbody>();
        }

        if (Input.GetKey(KeyCode.W))
        {
            Quaternion rotZ = Quaternion.AngleAxis(-1, new Vector3(0, 0, 1));
            gameObject.transform.rotation *= rotZ;


        }


        if(Input.GetKey(KeyCode.Space))
        {
            Vector3 position = new Vector3(nX, nY, nZ);
            Instantiate(prefub1, position, Quaternion.identity);

        }

        
    }
}
