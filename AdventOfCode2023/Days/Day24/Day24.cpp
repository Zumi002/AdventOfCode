#include "../../Utility/SupportFunc.h"
#include "Day24.h"
#include <set>
#include <memory>

#define ll long long 

struct Block
{
	long long x, y, z;
	long long vx, vy, vz;
	Block(ll X,ll Y,ll Z,ll vX,ll vY,ll vZ)
	{
		x = X;
		y = Y;
		z = Z;
		vx = vX;
		vy = vY;
		vz = vZ;
	}

	bool collide(Block a, ll areaMin, ll areaMax)
	{
		double aX = (double)vy / (double)vx;
		double bX = (double)a.vy / (double)a.vx;
		if (aX - bX == 0)return false;
		double s = aX - bX;
		double r = aX * (double)(x) - y + bX * (double)(-a.x) + a.y;
		double colP = r / s;
		double colH = aX * (colP - x) + y;
		if (colP <= areaMax && colP >= areaMin && colH <= areaMax && colH >= areaMin)
		{
			bool goodT =false, goodA=false;
			if (vx < 0 && colP < x)goodT = true;
			if (vx > 0 && colP > x)goodT = true;
			if (a.vx < 0 && colP < a.x)goodA = true;
			if (a.vx > 0 && colP > a.x)goodA = true;
			return goodT&&goodA;
		}
		return false;
	}
	bool collideR(Block a, ll areaMin, ll areaMax,ll rx,ll ry)
	{
		double aX = (double)(vy-ry) / (double)(vx-rx);
		double bX = (double)(a.vy-ry) / (double)(a.vx-rx);
		if (aX - bX == 0)return true;
		double s = aX - bX;
		double r = aX * (double)(x)-y + bX * (double)(-a.x) + a.y;
		double colP = r / s;
		double colH = aX * (colP - x) + y;
		if (colP <= areaMax && colP >= areaMin && colH <= areaMax && colH >= areaMin)
		{
			bool goodT = false, goodA = false;
			if (vx -rx<= 0 && colP <= x)goodT = true;
			if (vx-rx > 0 && colP > x)goodT = true;
			if (a.vx -rx<= 0 && colP <= a.x)goodA = true;
			if (a.vx -rx> 0 && colP > a.x)goodA = true;
			return goodT && goodA;
		}
		return false;
	}
	vector<double> collideP(Block a, ll areaMin, ll areaMax,ll rx,ll ry)
	{
		double aX = (double)(vy - ry) / (double)(vx - rx);
		double bX = (double)(a.vy - ry) / (double)(a.vx - rx);
		if (aX - bX == 0)return {};
		double s = aX - bX;
		double r = aX * (double)(x)-y + bX * (double)(-a.x) + a.y;
		double colP = r / s;
		double colH = (aX) * (colP - x) + y;
		if (colP <= areaMax && colP >= areaMin && colH <= areaMax && colH >= areaMin)
		{
			bool goodT = false, goodA = false;
			if (vx-rx < 0 && colP < x)goodT = true;
			if (vx -rx> 0 && colP > x)goodT = true;
			if (a.vx-rx < 0 && colP < a.x)goodA = true;
			if (a.vx-rx > 0 && colP > a.x)goodA = true;
			return {colP,colH};
		}
		return {};
	}
	bool collideRZ(Block a, ll areaMin, ll areaMax, ll rx, ll rz)
	{
		double aX = (double)(vz - rz) / (double)(vx - rx);
		double bX = (double)(a.vz - rz) / (double)(a.vx - rx);
		if (aX - bX == 0)return true;
		double s = aX - bX;
		double r = aX * (double)(x)-z + bX * (double)(-a.x) + a.z;
		double colP = r / s;
		double colH = aX * (colP - x) + z;
		if (colP <= areaMax && colP >= areaMin && colH <= areaMax && colH >= areaMin)
		{
			bool goodT = false, goodA = false;
			if (vx - rx <= 0 && colP <= x)goodT = true;
			if (vx - rx > 0 && colP > x)goodT = true;
			if (a.vx - rx <= 0 && colP <= a.x)goodA = true;
			if (a.vx - rx > 0 && colP > a.x)goodA = true;
			return goodT && goodA;
		}
		return false;
	}
	vector<double> collidePZ(Block a, ll areaMin, ll areaMax, ll rx, ll rz)
	{
		double aX = (double)(vz - rz) / (double)(vx - rx);
		double bX = (double)(a.vz - rz) / (double)(a.vx - rx);
		if (aX - bX == 0)return {};
		double s = aX - bX;
		double r = aX * (double)(x)-z + bX * (double)(-a.x) + a.z;
		double colP = r / s;
		double colH = (aX) * (colP - x) + z;
		if (colP <= areaMax && colP >= areaMin && colH <= areaMax && colH >= areaMin)
		{
			bool goodT = false, goodA = false;
			if (vx - rx < 0 && colP < x)goodT = true;
			if (vx - rx > 0 && colP > x)goodT = true;
			if (a.vx - rx < 0 && colP < a.x)goodA = true;
			if (a.vx - rx > 0 && colP > a.x)goodA = true;
			return { colP,colH };
		}
		return {};
	}

	bool goThr(ll rx, ll ry,vector<double> point)
	{
		double aX = (double)(vy - ry) / (double)(vx - rx);
		if (aX * (point[0] - x) + y == point[1])return true;
		return false;
	}
	bool goThrZ(ll rx, ll rz, vector<double> point)
	{
		double aX = (double)(vz - rz) / (double)(vx - rx);
		if (aX * (point[0] - x) + z == point[1])return true;
		return false;
	}

};


void Day24()
{
	myFile in = myFile();
	in.Open("Days/Day24/in.txt");
	in.ReadFile();

	vector<Block> stones;

	for (int i = 0; i < in.nol; i++)
	{
		vector<ll> pos;
		vector<ll> vel;
		for (int j = 0; j < 3; j++)
		{
			pos.push_back(strtoll(split(in.inputWords[i][j], ',')[0].c_str(), NULL, 10));
			vel.push_back(strtoll(split(in.inputWords[i][4+j], ',')[0].c_str(), NULL, 10));
		}
		stones.push_back(Block(pos[0], pos[1], pos[2], vel[0], vel[1], vel[2]));
	}
	int coll = 0;
	ll amax = LLONG_MAX,
		amin = 0;
	int range = 2000;
	vector<vector<double>> poss;
	vector<vector<double>> poss2;
	for (int rvx = 250; rvx <= range; rvx++)
	{
		for (int rvy = -179; rvy <= range; rvy++)
		{
			vector<double> colP;
			vector<int> para;
			bool br = true;
			for (int i = 0; i < stones.size()&&br; i++)
			{
				for (int j = i + 1; j < stones.size()&&br; j++)
				{
					if (stones[i].collideR(stones[j], amin, amax,rvx,rvy))
					{
						if (stones[i].collideP(stones[j], amin, amax, rvx, rvy).size() == 0)
						{
							para.push_back(i);
						}
						else
						{
							if (colP.size() == 0)colP = stones[i].collideP(stones[j], amin, amax, rvx, rvy);
							else if (colP != stones[i].collideP(stones[j], amin, amax, rvx, rvy)) br = false;
						}
					}
					else br = false;
				}
			}
			if (colP.size() > 1)
			{
				for (int i : para)
				{
					if (!stones[i].goThr(rvx, rvy, colP))
					{
						br = false;
						break;
					}
				}
				if (br)
				{

					poss.push_back(colP);
				}
			}
		}
		for (int rvz = 81; rvz <= range; rvz++)
		{
			vector<double> colP;
			vector<int> para;
			bool br = true;
			for (int i = 0; i < stones.size() && br; i++)
			{
				for (int j = i + 1; j < stones.size() && br; j++)
				{
					if (stones[i].collideRZ(stones[j], amin, amax, rvx, rvz))
					{
						if (stones[i].collidePZ(stones[j], amin, amax, rvx, rvz).size() == 0)
						{
							para.push_back(i);
						}
						else
						{
							if (colP.size() == 0)colP = stones[i].collidePZ(stones[j], amin, amax, rvx, rvz);
							else if (colP != stones[i].collidePZ(stones[j], amin, amax, rvx, rvz)) br = false;
						}
					}
					else br = false;
				}
			}
			if (colP.size() > 1)
			{
				for (int i : para)
				{
					if (!stones[i].goThrZ(rvx, rvz, colP))
					{
						br = false;
						break;
					}
				}
				if (br)
				{

					poss2.push_back(colP);
				}
			}
		}
	}
	for (auto v : poss)
	{
		cout << v[0] << " " << v[1] << "\n";
	}
	cout << "----\n";
	for (auto v : poss2)
	{
		cout << v[0] << " " << v[1] << "\n";
	}
	/*
	for (int i = 0; i < stones.size(); i++)
	{
		for (int j = i + 1; j < stones.size(); j++)
		{
			if (stones[i].collide(stones[j], amin, amax))
			{
				coll++;
			}
		}
	}*/
	cout << coll;
	
}