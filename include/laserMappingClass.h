// Author of ISCLOAM: Wang Han 
// Email wh200720041@gmail.com
// Homepage https://wanghan.pro

#ifndef _LASER_MAPPING_H_
#define _LASER_MAPPING_H_

//PCL lib
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl_ros/impl/transforms.hpp>

//eigen  lib
#include <Eigen/Dense>
#include <Eigen/Geometry>

//c++ lib
#include <string>
#include <math.h>
#include <vector>


#define LASER_CELL_WIDTH 10.0  //default: 50.0 
#define LASER_CELL_HEIGHT 10.0 //default: 50.0 
#define LASER_CELL_DEPTH 10.0  //default: 50.0 

//separate map as many sub point clouds
#define LASER_CELL_RANGE_HORIZONTAL 10  //default: 2 
#define LASER_CELL_RANGE_VERTICAL  10   //default: 2

//上面这两类参数和downSizeFilter.setLeafSize(0.5, 0.5, 0.5); 设置之间有影响，设置的不好的话，程序一运行就crash


class LaserMappingClass 
{

    public:
    	LaserMappingClass();
		void init(void);
		void resetMap(std::vector<Eigen::Isometry3d>& path);
		void updateCurrentPointsToMap(const pcl::PointCloud<pcl::PointXYZI>::Ptr& pc_in, const Eigen::Isometry3d& pose_current);
		pcl::PointCloud<pcl::PointXYZI>::Ptr getMap(void);
		std::vector<pcl::PointCloud<pcl::PointXYZI>::Ptr> point_cloud_arr;
		Eigen::Isometry3d last_pose;

	private:
		int origin_in_map_x;
		int origin_in_map_y;
		int origin_in_map_z;
		int map_width;
		int map_height;
		int map_depth;
		std::vector<std::vector<std::vector<pcl::PointCloud<pcl::PointXYZI>::Ptr>>> map;
		pcl::VoxelGrid<pcl::PointXYZI> downSizeFilter;
		
		void addWidthCellNegative(void);
		void addWidthCellPositive(void);
		void addHeightCellNegative(void);
		void addHeightCellPositive(void);
		void addDepthCellNegative(void);
		void addDepthCellPositive(void);
		void checkPoints(int& x, int& y, int& z);

};


#endif // _LASER_MAPPING_H_

