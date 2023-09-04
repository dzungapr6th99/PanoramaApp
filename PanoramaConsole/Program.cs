using System;
using System.IO;
using PanoramaClr;
namespace PanoramaConsole
{
    class Parnorama
    {
        static void Main()
        {
            string path1 = "C:\\Users\\admin\\source\\repos\\PanoramaApp\\PanoramaApp\\Hill1.JPG";
            string path2 = "C:\\Users\\admin\\source\\repos\\PanoramaApp\\PanoramaApp\\Hill2.JPG";
            List<string> list = new List<string>(); 
            list.Add(path1);
            list.Add(path2);
            PanoramaClr.Panorama.MergeImage(list);
        }
    }
}