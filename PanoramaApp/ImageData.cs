using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace PanoramaApp
{
    public class ImageInfo
    {
        public string FileName { get; set; }
        public int Width { get; set; }
        public int Height { get; set; }
        public int RGBImageCount { get; set; }
        public BitmapImage ImageData { get; set; }
    }
}
