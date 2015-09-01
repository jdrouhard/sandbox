#include <iostream>

void printArr(int* arr, int n)
{
    for (int i = 0; i < n; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void SpecialSort(int* arr, int n)
{
    int negCount = 0;
    for (int i =0; i < n; ++i)
    {
        if (arr[i] < 0)
        {
            negCount++;
        }
    }

    int posSwapStart = negCount;
    int negSwapStart = 0;
    for (int i = 0; i < negCount; ++i)
    {
        if (arr[i] > 0)
        {
            posSwapStart++;
        }
        else
        {
            negSwapStart++;
        }
    }

    int posFarSwapStart = posSwapStart;
    int negFarSwapStart = negSwapStart;
    for (int i = negCount; i < posSwapStart; ++i)
    {
        if (arr[i] > 0)
        {
            posFarSwapStart++;
        }
        else
        {
            negFarSwapStart++;
        }
    }
    for (int i = posSwapStart; i < posFarSwapStart; ++i)
    {
        if (arr[i] < 0)
        {
            negFarSwapStart++;
        }
    }

    int index = 0;
    int negSwapIndex = 0;
    int posSwapIndex = negCount;
    bool indexMoved = true;
    int negMidSwapIndex = negSwapStart;
    int posMidSwapIndex = posSwapStart;
    int negFarSwapIndex = negFarSwapStart;
    int posFarSwapIndex = posFarSwapStart;
    int movedFromPos = 0;

    while (posSwapIndex < n && index < negCount)
    {
        printArr(arr, n);
        //std::cout << "index: " << index << std::endl;
        //std::cout << "negSwapIndex: " << negSwapIndex << std::endl;
        //std::cout << "posSwapIndex: " << posSwapIndex << std::endl;
        //std::cout << "negMidSwapIndex: " << negMidSwapIndex << std::endl;
        //std::cout << "posMidSwapIndex: " << posMidSwapIndex << std::endl;
        //std::cout << "negFarSwapIndex: " << negFarSwapIndex << std::endl;
        //std::cout << "posFarSwapIndex: " << posFarSwapIndex << std::endl;
        //std::cout << "negCount: " << negCount << std::endl;
        //std::cout << "negSwapStart: " << negSwapStart << std::endl;
        //std::cout << "posSwapStart: " << posSwapStart << std::endl;
        //std::cout << "negFarSwapStart: " << negFarSwapStart << std::endl;
        //std::cout << "posFarSwapStart: " << posFarSwapStart << std::endl;
        //std::cout << "indexMoved: " << indexMoved << std::endl;
        //std::cout << "movedFromPos: " << movedFromPos << std::endl;
        //std::cout << std::endl;

        if (arr[index] < 0)
        {
            if (indexMoved)
            {
                if (index == negSwapIndex)
                {
                    index++;
                    negSwapIndex++;
                    continue;
                }
                std::swap(arr[index], arr[negSwapIndex++]);
                movedFromPos = negSwapIndex - 1;
                indexMoved = false;
            }
            else if (movedFromPos >= negCount && movedFromPos < posSwapStart)
            {
                std::swap(arr[index], arr[negMidSwapIndex++]);
                movedFromPos = negMidSwapIndex - 1;
                indexMoved = false;
            }
            else if (movedFromPos >= posFarSwapStart)
            {
                std::swap(arr[index], arr[negFarSwapIndex++]);
                movedFromPos = negFarSwapIndex - 1;
                indexMoved = false;
            }
            else
            {
                while (index < negSwapIndex)
                {
                    index++;
                }

                indexMoved = true;
            }
        }
        else
        {
            if (indexMoved || movedFromPos < negCount)
            {
                std::swap(arr[index], arr[posSwapIndex++]);
                movedFromPos = posSwapIndex - 1;
                indexMoved = false;
            }
            else if (movedFromPos >= negCount && movedFromPos < posSwapStart)
            {
                std::swap(arr[index], arr[posMidSwapIndex++]);
                movedFromPos = posMidSwapIndex - 1;
                indexMoved = false;
            }
            else
            {
                std::swap(arr[index], arr[posFarSwapIndex++]);
                movedFromPos = posFarSwapIndex - 1;
                indexMoved = false;
            }
        }
    }
}


int main()
{
    int arr[] = { -1, 1, 3, -2, 2, 5, -3, -7, 6, 10, 18, -5, 20, 3, -6 };

    int size = sizeof(arr) / sizeof(int);

    SpecialSort(arr, size);

    printArr(arr, size);

}

