using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;

namespace PanoramaApp
{
    public class FileHelper
    {
        #region parameter

        private string c_FullFilePath;
        private string c_PathName;
        private string c_FileName;

      
        #endregion


        public FileHelper(string p_PathFile)
        {
            
            try
            {
                
                
                c_FullFilePath =Directory.GetCurrentDirectory() + Path.DirectorySeparatorChar + p_PathFile;
                if (!Directory.Exists(c_FullFilePath))
                    Directory.CreateDirectory(c_FullFilePath);
                //c_StreamReader = new StreamReader(c_PathName, true);
            }
            catch (Exception ex)
            {

            }
        }
   

        public void SaveImage(Bitmap Image)
        {
            try
            {
                Image.Save(c_FullFilePath + Path.DirectorySeparatorChar + DateTime.Now.ToString("hhmmss") + ".jpg");
            }
            catch
            {

            }
        }

    }
}
