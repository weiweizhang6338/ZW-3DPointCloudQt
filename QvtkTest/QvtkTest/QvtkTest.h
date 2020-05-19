#pragma once

#include <pcl/common/common_headers.h>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/common/common.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vtkGenericOpenGLRenderWindow.h>

#include <QtWidgets/QWidget>

#include "ui_QvtkTest.h"

class QvtkTest : public QWidget {
  Q_OBJECT

 public:
  QvtkTest(QWidget *parent = Q_NULLPTR);

 protected:
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;

 private:
  Ui::QvtkTestClass ui;
  void initialVtkWidget();
};
