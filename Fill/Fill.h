#pragma once
#include <fstream>
#include <queue>
#include <array>
#include <memory>

const int canvas_width = 100;
const int canvas_height = 100;
const char space_char = ' ';
const char border_char = '#';
const char start_point_char = 'O';
const char fill_point_char = '.';

using Canvas = std::array<std::array<char, canvas_width>, canvas_height>;
using Coords = std::pair<int, int>;
using CoordsQueue = std::queue<Coords>;

struct CanvasInfo
{
	std::shared_ptr<Canvas> canvas;
	std::shared_ptr<CoordsQueue> startCoords;
};

std::shared_ptr<Canvas> InitializeCanvas()
{
	std::shared_ptr<Canvas> canvas = std::make_shared<Canvas>();

	for (auto& arr : *canvas)
		arr.fill(' ');

	return canvas;
}

CanvasInfo ReadCanvasFromFile(std::ifstream& file)
{
	std::shared_ptr<Canvas> canvas = InitializeCanvas();
	std::shared_ptr<CoordsQueue> coords = std::make_shared<CoordsQueue>();

	char ch{};
	int i{}; int j{};

	while (file.get(ch))
	{
		if (ch == start_point_char)
			coords->push(std::pair(i, j));

		if (ch == '\n')
		{
			i++; 
			j = 0;
			continue;
		}

		if (j == canvas_width) // Пропускаем все, что правее 100 единиц
		{
			i++;
			j = 0;
			std::string line{};
			std::getline(file, line);
			continue;
		}

		if (i == canvas_height) // Пропускаем все, что ниже 100 единиц
		{
			break;
		}

		canvas->at(i).at(j) = ch; 
		j++;
		continue;
	}

	if (file.bad())
		throw std::ifstream::failure("Unable to read canvas from file");

	return CanvasInfo{ canvas, coords };
}

bool IsCellEmpty(const Canvas& canvas, const Coords& coords)
{
	return canvas[coords.first][coords.second] == space_char;
}

void CheckNeighboursWithFillingAndPushingToQueue(CoordsQueue& qu, Canvas& canvas, const Coords& coords)
{
	int i = coords.first;
	int j = coords.second;

	int _j = j - 1;
	if (_j >= 0 && IsCellEmpty(canvas, { i, _j }))
	{
		qu.push(std::pair(i, _j));
		canvas[i][_j] = '.';
	}

	_j = j + 1;
	if (_j < canvas_width && IsCellEmpty(canvas, { i, _j }))
	{
		qu.push(std::pair(i, _j));
		canvas[i][_j] = '.';
	}

	int _i = i - 1;
	if (_i >= 0 && IsCellEmpty(canvas, { _i, j }))
	{
		qu.push(std::pair(_i, j));
		canvas[_i][j] = '.';
	}

	_i = i + 1;
	if (_i < canvas_height && IsCellEmpty(canvas, { _i, j }))
	{
		qu.push(std::pair(_i, j));
		canvas[_i][j] = '.';
	}
}

std::shared_ptr<Canvas> FillCanvas(const CanvasInfo& canvasInfo)
{
	std::shared_ptr<Canvas> filledCanvas = std::make_shared<Canvas>(*canvasInfo.canvas);
	CoordsQueue coordsQueue = *canvasInfo.startCoords;

	if (coordsQueue.empty())
		return filledCanvas;

	while (!coordsQueue.empty())
	{
		Coords coords = coordsQueue.front();
		coordsQueue.pop();
		CheckNeighboursWithFillingAndPushingToQueue(coordsQueue, *filledCanvas, coords);
	}

	return filledCanvas;
}

void WriteToStream(const Canvas& canvas, std::ostream& os)
{
	for (int i = 0; i < canvas_height; i++)
	{
		for (int j = 0; j < canvas_width; j++)
		{
			os << canvas[i][j];
			if (!os)
				throw std::ostream::failure("Unable to write canvas to stream");
		}
		os << '\n';
	}
	os.flush();
}