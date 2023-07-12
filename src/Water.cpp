#include "Water.h"
#include "Types.h"
#include <random>
using namespace WMB;


double Dista(Location src, Location dest)
{
	double y = pow(dest.i - src.i, 2);
	double x = pow(dest.j - src.j, 2);
	return sqrt(x + y);
}

void Water::StartUp()
{
	std::cout << "(Water) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadTiles(path, image, tiles);
	//std::cout << "color: " << color << "\n";


	std::cout << "(Water) Start Complete\n";
}

void Water::Draw(Bmp& userBmp, Bmp& canvas, int width, int height)
{
	std::vector<Pixel> uc;

	std::cout << "(Water) Started Drawing\n";

	DrawWaterBorder(userBmp, canvas, width, height);

	//Loop throught the userBmp
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{

			//tracks locations used for validation
			std::vector<Location> locations;
			bool isValid = ValidSpot(userBmp, canvas, i, j, locations);
			if (isValid)
			{
				//make sure nothing else use these pixels
				MarkUsed(userBmp, locations);

				//draw the tile
				DrawTile(userBmp, canvas, Location(i, j));

			}

		}

	}

	dw.Draw(userBmp, canvas, width, height);
	
	std::cout << "(Water) Done Drawing\n";
}

/**
* Draw the bmp at the location on the canvas
* location should be the center of the bmp
*/
void Water::DrawTile(Bmp& userBmp, Bmp& canvas, Location location)
{
	//Get the bmp to draw
	int index = rand() % tiles.size();

	//Calc Offset
	int xOffset = (rand() % (tiles[index].offset.x * 2 + 1)) - tiles[index].offset.x;
	int yOffset = (rand() % (tiles[index].offset.y * 2 + 1)) - tiles[index].offset.y;
	location.i += yOffset;
	location.j += xOffset;

	//Get the tile's bmp
	Bmp bmp = tiles[index].bmp;

	//Get The Bounds
	int height = bmp.size();
	int width = bmp[0].size();

	//Convert from bmp space to canvas space
	auto BmpToCanvas = [&](int i, int j, Location location)
	{
		int x = location.i + (i - height / 2);
		int y = location.j + (j - width / 2);

		return Location(x, y);
	};

	//Check if valid canvas space pos
	auto IsValidPos = [&](Location location)
	{
		if (location.i < 0 || location.i >= canvas.size()) { return false; }
		if (location.j < 0 || location.j >= canvas[0].size()) { return false; }
		return true;
	};


	//std::cout << "MADE IT HERE\n";
	//std::cout << "Center: " << location << "\n";

	//loop through the mountain bmp
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{

			//Draw only the valid color 
			if (tiles[index].bmp[i][j] == BLACK)
			{

				//Location in the canvas
				Location canvasPos = BmpToCanvas(i, j, location);

				bool isValid = IsValidPos(canvasPos);
				
				//valid position
				//&& it is drawing on a water tile
				if (isValid && (userBmp[canvasPos.i][canvasPos.j] == color || userBmp[canvasPos.i][canvasPos.j] == ~color))
				{
					canvas[canvasPos.i][canvasPos.j] = BLACK;
				}
			}
		}
	}
}



/*
* Draws a line where water meets anything that is not water (aka land, mountain, etc)
*/
void Water::DrawWaterBorder(Bmp& userBmp, Bmp& canvas, int height, int width)
{
	//Is the position valid on the canvas
	auto IsValid = [&](int i, int j)
	{
		if (i < 0 || i >= height) { return false; }
		if (j < 0 || j >= width) { return false; }
		return true;
	};

	/*
	* Check the adjacent pixels to see if next to land
	* true, if next to land
	* false, if surrounded by water
	*/
	auto Check4 = [&](int i, int j)
	{	
		if (IsValid(i - 1, j)) //Above
		{
			//Not a water color
			if (userBmp[i-1][j] != color && userBmp[i-1][j] != ~color) { return true; }
		}
		if (IsValid(i + 1, j)) //Below
		{
			//Not a water color
			if (userBmp[i + 1][j] != color && userBmp[i + 1][j] != ~color) { return true; }
		}
		if (IsValid(i, j - 1)) //Left
		{
			//Not a water color
			if (userBmp[i][j-1] != color && userBmp[i][j-1] != ~color) { return true; }
		}
		if (IsValid(i, j + 1)) //Reft
		{
			//Not a water color
			if (userBmp[i][j + 1] != color && userBmp[i][j + 1] != ~color) { return true; }
		}
		return false;
	};


	//Loop through the userBmp
	for (int i = 0; i < height; i += 1)
	{
		for (int j = 0; j < width; j += 1)
		{
			//if a water pixel
			if (userBmp[i][j] == color || userBmp[i][j] == ~color)
			{
				//if next to land
				if (Check4(i, j))
				{
					canvas[i][j] = BLACK;
					dw.borders.push_back(Location(i, j));
				}
			}

		}
	}
}



void DeepWater::StartUp()
{
	std::cout << "(DeepWater) Starting Up\n";
	Bitmap image;
	Bitmap b;

	LoadTiles(path, image, tiles);
	//std::cout << "color: " << color << "\n";


	std::cout << "(DeepWater) Start Complete\n";
}


void DeepWater::Draw(Bmp& userBmp, Bmp& canvas, int width, int height)
{
	std::cout << "(DeepWater) Started Drawing\n";
	std::cout << "# of borders " << borders.size() << "\n";
	std::vector<Location> locations = FindAllDeepWater(userBmp, width, height);
	std::cout << "Found " << locations.size() << " Deepwaters\n";
	std::vector<std::vector<Location>> clusters = ClusterDeepWater(locations);
	std::cout << "Formed " << clusters.size() << " clusters\n";

  //DEBUG: meant to visualize the clusters
	//DrawCluster(clusters, canvas);

	std::vector<Location> centers = GetClusterCenter(clusters);

	std::vector< std::pair<Location, std::pair<int, int>>> clusterCenter_width_height = CalcClusterSize(userBmp, width, height, clusters, centers);
 
  //slowly fade out waves that were drawn on the cluster
  for(int i = 0; i < clusters.size(); i += 1)
  {
    int thing = 1;
    for(const auto& loc : clusters[i])
    {
      
      //find distance of wave from center
      //the closer it is the more faded
      int x = abs(loc.i - centers[i].i);
      int y = abs(loc.i - centers[i].j);
      if(x == 0 && y == 0) {continue;}
      


      int w = clusterCenter_width_height[i].second.first / 2; 
      int h = clusterCenter_width_height[i].second.second / 2;
      
      double ax = abs(x/w - 1);
      double ay = abs(y/h - 1);
      double alpha = (1 - 1/(Dista(loc, centers[i])));
      
      std::cout << "alpha: " << alpha << "\n";

      Pixel cap = canvasPixel;
      canvas[loc.i][loc.j] = (canvas[loc.i][loc.j] * alpha) + (cap * (1 - alpha));
    }
  }
	
	std::cout << "(DeepWater) Done Drawing\n";

}

//Calculate the Size for a tile to fit into for each cluster
std::vector < std::pair<Location, std::pair<int, int>>> DeepWater::CalcClusterSize(Bmp& userBmp, int width, int height, std::vector<std::vector<Location>> clusters, std::vector<Location> centers)
{
	std::vector < std::pair<Location, std::pair<int, int>>> cluster_width_height;

	//find the width and height of each cluster starting from the centers
	for (int u = 0; u < clusters.size(); u += 1)
	{
		const auto& center = centers[u];
		int width_count = 0;
		int height_count = 0;

		//going left
		for (int j = center.j; j > 0; j -= 1)
		{
			Location l = Location(center.i, j);
			for (const auto& loc : clusters[u])
			{
				if (l == loc)
				{
					width_count += 1;
				}
			}
		}

		//going right
		for (int j = center.j; j < width; j += 1)
		{
			Location l = Location(center.i, j);
			for (const auto& loc : clusters[u])
			{
				if (l == loc)
				{
					width_count += 1;
				}
			}
		}

		//going up
		for (int i = center.i; i > 0; i -= 1)
		{
			Location l = Location(i, center.j);
			for (const auto& loc : clusters[u])
			{
				if (l == loc)
				{
					height_count += 1;
				}
			}
		}

		//going down
		for (int i = center.i; i < height; i += 1)
		{
			Location l = Location(i, center.j);
			for (const auto& loc : clusters[u])
			{
				if (l == loc)
				{
					height_count += 1;
				}
			}
		}

  std::pair<int,int> w_h(width_count, height_count);
  std::pair<Location, std::pair<int,int>> c_w_h(center, w_h);

		cluster_width_height.push_back(c_w_h);
	}

	for (const auto& c_w_h : cluster_width_height)
	{
		std::cout << "Center: " << c_w_h.first << " width: " << c_w_h.second.first << " height: " << c_w_h.second.second << "\n";
	}

	return cluster_width_height;
}

void DeepWater::DrawCluster(std::vector<std::vector<Location>> clusters, Bmp& canvas)
{
	int i = 0;
	for (const auto& cluster : clusters)
	{
		std::cout << "i: " << i << "\n";
		int amount = ((255 / clusters.size()) * i);
		std::cout << "amount: " << amount << "\n";
		for (const auto& loc : cluster)
		{
			canvas[loc.i][loc.j] = Pixel(255 - amount, 0, 0);
		}
		i += 1;
	}

	//TODO: REMOVE REPLACE WITH A PARAMETER
	std::vector<Location> centers = GetClusterCenter(clusters);

	//Draw Centers of each clusters
	for (const auto& loc : centers)
	{
		std::cout << "loc: " << loc << "\n";
		canvas[loc.i][loc.j] = Pixel(0, 0, 0);
	}

}

//Finds the center of each cluster
std::vector<Location> DeepWater::GetClusterCenter(std::vector<std::vector<Location>> clusters)
{
	std::vector<Location> centers;

	//loop through each cluster
	for (const auto& cluster : clusters)
	{
		Location center = Location(0, 0);
		
		//Loop through all locations in the cluster
		for (const auto& loc : cluster)
		{
			center += loc;
			
		}
		center /= (int)cluster.size();
		
		centers.push_back(center);
	}

	return centers;
}



/*
* Returns a list of Water tiles that are Deep
* 
* Criteria to be DeepWater:
* Must be X pixels away from any non water blocks
*/

std::vector<Location> DeepWater::FindAllDeepWater(Bmp userBmp, int width, int height)
{
	std::vector<Location> locations;

	//loop through the userBmp
	for (int i = 0; i < height; i += 1)
	{
		
    for (int j = 0; j < width; j += 1)
		{
		
      //must be water block
			if (userBmp[i][j] == color || userBmp[i][j] == ~color)
			{
				Location loc = Location(i, j);
				 
				float dist = 100;
				
        //find distance to land from curr position
				for (const auto& border : borders)
				{
					float newDist = abs(Dista(loc, border));
					if (newDist < dist) { dist = newDist; }
				}

        //if the smallest distance from land is farther than min dist
				if (dist >= distance)
				{
					locations.push_back(loc);
				}
			}
		}
	}

	return locations;
}

//Return Clusters of DeepWaters
std::vector<std::vector<Location>> DeepWater::ClusterDeepWater(std::vector<Location> deepWaters)
{
	//clusters to return
	std::vector<std::vector<Location>> clusters;
	
	//make each element in the things a cluster
	for (int i = 0; i < deepWaters.size(); i += 1)
	{
    //make empty vector
		std::vector<Location> loc;
		
    //store the curr location to it
    loc.push_back(deepWaters[i]);
	  
    //add to clusters
    clusters.push_back(loc);
	}


	//Determine if any two points in the clusters are close
	auto ClusterClose = [&](std::vector<Location> c1, std::vector<Location> c2)
	{
		//if either clusters are empty
		if (c1.size() == 0 || c2.size() == 0) { return false; }
		for (int i = 0; i < c1.size(); i += 1)
		{
			for (int j = 0; j < c2.size(); j += 1)
			{
				if (abs(Dista(c1[i], c2[j])) <= 1.0f)
				{
					return true;
				}
			}
		}
		return false;
	};


	bool changed = false;
	
	//loop until no new clusters are made
	while (true)
	{
    
    //track if a cluster was formed
    changed = false;
		
    //form clusters
		for (int i = 0; i < clusters.size(); i += 1)
		{
	
      for (int j = i+1; j < clusters.size(); j += 1)
			{
				
        //see if either of the clusters are close to eachother
        if (ClusterClose(clusters[i], clusters[j]))
				{
					
          //add points from one cluster to another
					clusters[i].insert(clusters[i].end(), clusters[j].begin(), clusters[j].end());
					clusters[j].clear();
					changed = true;
				
        }
			}
		}
    
    //if true - no clusters were formed
    if (!changed)
		{
			break;
		}

  }

  //remove all clusters that have nothing in them	
  std::vector<std::vector<Location>> clusters_slimed;
	for (const auto& c : clusters)
	{
		if (c.size() > 0)
		{
			clusters_slimed.push_back(c);
		}
	}

	return clusters_slimed;

}


