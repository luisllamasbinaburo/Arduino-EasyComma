/***************************************************
Copyright (c) 2017 Luis Llamas
(www.luisllamas.es)

Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License
****************************************************/


#include "EasyCommaLib.h"

EasyComma::EasyComma(size_t capacity)
{
	_capacity = capacity;
	_items = new int[capacity];
}

EasyComma::~EasyComma()
{
	delete[] _items;
}

int& EasyComma::operator[](const size_t index)
{
	return _items[index];
}

void EasyComma::Recieve(Action okCallback)
{
	if (Serial.available())
	{
		char incomingChar = Serial.read();

		if (incomingChar >= '0' && incomingChar <= '9')
		{
			_currentItem = _currentItem * 10 + (incomingChar - '0');
		}
		else if (incomingChar == Separator)
		{
			_items[_currentIndex] = _currentItem;
			_currentCount++;
			if (++_currentIndex >= _capacity) _currentIndex = 0;
			_currentItem = 0;
		}
		else if (incomingChar == EndSeparator)
		{
			_items[_currentIndex] = _currentItem;
			
			_count = _currentCount + 1;
			_lastIndex = _currentIndex;
			_currentCount = 0;
			_currentItem = 0;
			_currentIndex = 0;

			if(okCallback!= nullptr) okCallback();
		}
	}
}

size_t EasyComma::Capacity()
{
	return _capacity;
}

size_t EasyComma::LastIndex()
{
	return _lastIndex;
}

size_t EasyComma::Count()
{
	return _count;
}

bool EasyComma::IsOverflow()
{
	return _count >= _capacity;
}