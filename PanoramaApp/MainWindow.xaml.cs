using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Windows;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using PanoramaClr;
using System.IO;

namespace PanoramaApp
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<string> Paths;
        FileHelper fHelper;
        Bitmap ImageResult;
        public MainWindow()
        {
            Paths = new List<string>();
            fHelper = new FileHelper(DateTime.Now.ToString("yyyyymmdd"));
            InitializeComponent();
        }
        private void MenuItem_Browser_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog runExplorer = new OpenFileDialog();
            runExplorer.Filter = "Image file|*.jpg;*.png";
            if (runExplorer.ShowDialog() == true)
            {
                string path = runExplorer.FileName;
                Paths.Add(path);
                BitmapImage ImgSource = CreateThumbnail(path,100);
                txtImageCount.Content = $"Image Count: {Paths.Count}";
                txtRGBCount.Content = $"Total RGB Count: {Paths.Count}";
                ImageInfo imageInfo = new ImageInfo()
                {
                    FileName = path,
                    RGBImageCount = Paths.Count,
                    Height = 100,
                    Width = 100,
                    ImageData = ImgSource
                };
                lsvImageSource.Items.Add(imageInfo);
            }
            else
            {
                return;
            }


        }
        #region Các hàm trên màn hình
        private void MergeImage_Click(object sender, RoutedEventArgs e)
        {
            String s = DateTime.Now.ToString() +".png";
            ImageResult = Panorama.MergeImage(Paths, s);
            BitmapImage bmpImage = BitmapToImageSource(ImageResult);
            ImgResult.Source = bmpImage;
            Paths.Clear();
        }

        private void SaveImage_Click(object sender, RoutedEventArgs e)
        {
            fHelper.SaveImage(ImageResult);
        }
        #endregion

        #region CÁc hàm bổ trợ
        BitmapImage BitmapToImageSource(Bitmap bitmap)
        {
            using (MemoryStream memory = new MemoryStream())
            {
                bitmap.Save(memory, System.Drawing.Imaging.ImageFormat.Bmp);
                memory.Position = 0;
                BitmapImage bitmapimage = new BitmapImage();
                bitmapimage.BeginInit();
                bitmapimage.StreamSource = memory;
                bitmapimage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapimage.EndInit();

                return bitmapimage;
            }
        }

        private int GetTotalRGBCount(string[] imageFiles)
        {
            int totalRGBCount = 0;

            foreach (string imagePath in imageFiles)
            {
                using (Image image = Image.FromFile(imagePath))
                {
                    Bitmap bitmap = new Bitmap(image);

                    if (ContainsRGBPixels(bitmap))
                    {
                        totalRGBCount++;
                    }
                }
            }

            return totalRGBCount;
        }
        private void UpdateImageInfo(int imageCount, int rgbCount)
        {
            txtImageCount.Content = $"Image Count: {imageCount}";
            txtRGBCount.Content = $"Total RGB Count: {rgbCount}";
        }

        private bool ContainsRGBPixels(Bitmap bitmap)
        {
            for (int x = 0; x < bitmap.Width; x++)
            {
                for (int y = 0; y < bitmap.Height; y++)
                {
                    Color pixelColor = bitmap.GetPixel(x, y);

                    if (pixelColor.R != pixelColor.G || pixelColor.R != pixelColor.B)
                    {
                        return true; // Return true if an RGB pixel is found
                    }
                }
            }

            return false;
        }


        private BitmapImage CreateThumbnail(string imagePath, int size)
        {
            BitmapImage thumbnail = new BitmapImage();

            thumbnail.BeginInit();
            thumbnail.CacheOption = BitmapCacheOption.OnLoad;
            thumbnail.UriSource = new Uri(imagePath);
            thumbnail.DecodePixelWidth = size;
            thumbnail.DecodePixelHeight = size;
            thumbnail.EndInit();

            return thumbnail;
        }
    }
    #endregion
}
