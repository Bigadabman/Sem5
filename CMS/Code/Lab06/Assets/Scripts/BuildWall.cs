using UnityEngine;

public class BuildWall : MonoBehaviour
{
    public GameObject prefub1;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Vector3 position = new Vector3(0, 0.5f, 0);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 4; j++)
            {

                Instantiate(prefub1, position, Quaternion.identity);
                position += new Vector3(0, 1, 0);
            }
            position = new Vector3(i + 1, 0.5f, 0);
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
