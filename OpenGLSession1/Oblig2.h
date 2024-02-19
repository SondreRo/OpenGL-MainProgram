#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <Eigen/Dense>
#include <iostream>
#include "Vertex.h"
#include "AppManager.h"

class Oblig2
{
public:

	static float GetY(Eigen::Vector3f& InABC, float X)
	{
		float A = InABC[0];
		float B = InABC[1];
		float C = InABC[2];

		return (A * X * X + B * X + C);
	}

	static float GetY2(Eigen::Vector4f& InABC, float X)
	{
		float A = InABC[0];
		float B = InABC[1];
		float C = InABC[2];
		float D = InABC[3];

		return (A * X * X * X + B * X * X + C * X + D);
	}
	
	static void GetGetPointsOnLine(Eigen::Vector3f& InABC, float start, float end, float step, std::vector<Vertex>& VectorToFill)
	{
		for (float x = start; x < end; x += step)
		{
			Vertex NewVertex;

			float y = GetY(InABC, x);
			float z = 0;

			NewVertex.Position = glm::vec3(x, y, z);

			VectorToFill.push_back(NewVertex);
		}
	}

	static void GetGetPointsOnLine2(Eigen::Vector4f& InABC, float start, float end, float step, std::vector<Vertex>& VectorToFill)
	{
		for (float x = start; x < end; x += step)
		{
			Vertex NewVertex;

			float y = GetY2(InABC, x);
			float z = 0;

			NewVertex.Position = glm::vec3(x, y, z);

			VectorToFill.push_back(NewVertex);
		}
	}
	static std::vector<Vertex> Oppgave1(std::vector<Vertex> ListToMakePointsFrom)
	{
		//std::vector<Vertex> ListOfPoints =
		//{
		//	Vertex(1,1,1),
		//	Vertex(1.5,3,1),
		//	Vertex(2.5,4,1),
		//	Vertex(4,2,1),
		//	Vertex(6,5,1),
		//	Vertex(6.5,3.5,1),
		//	Vertex(7,7,1),
		//};

		/*std::vector<std::vector<float>> MyVector;
		MyVector[5][7] = 5;*/

		std::vector<Vertex> PointsToReturn;

		Eigen::MatrixXf A(ListToMakePointsFrom.size(), 3);
		Eigen::VectorXf B(ListToMakePointsFrom.size());

	
		for (int i{0}; i < ListToMakePointsFrom.size(); i++)
		{
			A(i, 0) = ListToMakePointsFrom[i].Position[0] * ListToMakePointsFrom[i].Position[0];
			A(i, 1) = ListToMakePointsFrom[i].Position[0];
			A(i, 2) = 1;

			B(i) = ListToMakePointsFrom[i].Position[1];
		}
		
		//A <<
		//	1.0, 1.0, 1.0,
		//	2.25, 1.5, 1.0,
		//	6.25, 2.5, 1.0,
		//	16.0, 4.0, 1.0,
		//	32.0, 6.0, 1.0,
		//	42.25, 6.5, 1.0,
		//	49.0, 7.0, 1.0;
		//B <<
		//	1.0f,
		//	3.0f,
		//	4.0f,
		//	2.0f,
		//	5.0f,
		//	3.5f,
		//	7.0f;

		Eigen::Vector3f solution = A.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(B);

		std::cout << solution << std::endl;

		float Bot = 1000000;
		float Top = -1000000;
		for (auto Point : ListToMakePointsFrom)
		{
			if (Point.Position.x < Bot)
				Bot = Point.Position.x;
			if (Point.Position.x > Top)
				Top = Point.Position.x;
		}
		
		GetGetPointsOnLine(solution, Bot, Top, 0.1, PointsToReturn);
		return PointsToReturn;
	}

	static std::vector<Vertex> Oppgave2(std::vector<Vertex> ListToMakePointsFrom)
	{
		std::vector<Vertex> PointsToReturn;

		Eigen::MatrixXf A(ListToMakePointsFrom.size(), 4);
		Eigen::Vector4f B(ListToMakePointsFrom.size());

	
		for (int i{0}; i < ListToMakePointsFrom.size(); i++)
		{
			A(i, 0) = ListToMakePointsFrom[i].Position[0] * ListToMakePointsFrom[i].Position[0] * ListToMakePointsFrom[i].Position[0];
			A(i, 1) = ListToMakePointsFrom[i].Position[0] * ListToMakePointsFrom[i].Position[0];
			A(i, 2) = ListToMakePointsFrom[i].Position[0];
			A(i, 3) = 1;

			B(i) = ListToMakePointsFrom[i].Position[1];
		}

		Eigen::Vector4f solution = A.inverse() * B;


		float Bot = 1000000;
		float Top = -1000000;
 		for (auto Point : ListToMakePointsFrom)
		{
			if (Point.Position.x < Bot)
				Bot = Point.Position.x;
 			if (Point.Position.x > Top)
 				Top = Point.Position.x;
		}

		
		GetGetPointsOnLine2(solution, Bot, Top, 0.1, PointsToReturn);
		return PointsToReturn;
	}
};

