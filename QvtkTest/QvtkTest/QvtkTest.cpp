#include "QvtkTest.h"

QvtkTest::QvtkTest(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
  initialVtkWidget();
  // Create example point cloud
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr point_cloud_ptr(
      new pcl::PointCloud<pcl::PointXYZRGB>);
  std::uint8_t r(255), g(15), b(15);
  for (float z(-1.0); z <= 1.0; z += 0.05) {
    for (float angle(0.0); angle <= 360.0; angle += 5.0) {
      pcl::PointXYZRGB point;
      point.x = 0.5 * std::cos(pcl::deg2rad(angle));
      point.y = sinf(pcl::deg2rad(angle));
      point.z = z;
      std::uint32_t rgb =
          (static_cast<std::uint32_t>(r) << 16 |
           static_cast<std::uint32_t>(g) << 8 | static_cast<std::uint32_t>(b));
      point.rgb = *reinterpret_cast<float *>(&rgb);
      point_cloud_ptr->points.push_back(point);
    }
    if (z < 0.0) {
      r -= 12;
      g += 12;
    } else {
      g -= 12;
      b += 12;
    }
  }
  point_cloud_ptr->width = (int)point_cloud_ptr->points.size();
  point_cloud_ptr->height = 1;
  // Show point cloud in viewer
  viewer->setBackgroundColor(0, 0, 0);
  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(
      point_cloud_ptr);
  viewer->addPointCloud<pcl::PointXYZRGB>(point_cloud_ptr, rgb, "sample cloud");
  viewer->setPointCloudRenderingProperties(
      pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  viewer->addCoordinateSystem(1.0);
  viewer->initCameraParameters();
  ui.openGLWidget->update();
}

void QvtkTest::initialVtkWidget() {
  viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
  vtkNew<vtkGenericOpenGLRenderWindow> window;
  window->AddRenderer(viewer->getRendererCollection()->GetFirstRenderer());
  ui.openGLWidget->SetRenderWindow(window.Get());
  viewer->setupInteractor(ui.openGLWidget->GetInteractor(),
                          ui.openGLWidget->GetRenderWindow());
  ui.openGLWidget->update();
}
