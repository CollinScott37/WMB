#pragma once
#include "Environment.h"
#include "Types.h"

namespace WMB
{
	
	class DeepWater : Environment
	{
	public:
		void StartUp();
		void Draw(Bmp& userbmp, Bmp& canvas, int width, int height);
		
		//a list of locations that mark the border between water and land
		std::vector<Location> borders;

		DeepWater()
		{
			color = Pixel(0, 161, 255);
			distance = 10.0f;
		}

		DeepWater(float dist)
		{
			distance = dist;
		}

	private:
		string path = "Water/Creatures";
		float distance; //distance from the land
			
		//Returns a list of Water tiles that are Deep
    	//Location of DeepWater, distnce from 
		std::vector<Location> FindAllDeepWater(Bmp userBmp, int width, int height);
		
		//Return Clusters of DeepWaters
		std::vector<std::vector<Location>> ClusterDeepWater(std::vector<Location> deepWaters);


		//Adds alpha to DeepWater
        void ApplyAlpha(Bmp &canvas, std::vector<std::vector<Location>> clusters, std::vector<Location> centers, std::vector<std::pair<Location, std::pair<int, int>>> clusterCenter_width_height);

        //DEBUG: Draws the clusters onto the canvas
		void DrawCluster(std::vector<std::vector<Location>> clusters, Bmp& canvas);

		//Finds the center of each cluster
		std::vector<Location> GetClusterCenter(std::vector<std::vector<Location>> clusters);

		//Calculate the Size for a tile to fit into for each cluster
		std::vector < std::pair<Location, std::pair<int, int>>> CalcClusterSize(Bmp& userBmp, int width, int height, std::vector<std::vector<Location>> clusters, std::vector<Location> centers);

	};

	class Water : public Environment
	{

	public:
		void StartUp();
		void Draw(Bmp& userBmp, Bmp& canvas, int width, int height);
		void DrawTile(Bmp& userBmp, Bmp& canvas, Location location);
		void DrawWaterBorder(Bmp& userBmp, Bmp& canvas, int height, int width);
		Water()
		{
			path = ppath + "Water/";
			color = Pixel(0,161, 255);
			size = 8;
		}



	private:
		DeepWater dw = DeepWater();

	};

}
