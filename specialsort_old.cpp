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

    int posToPosSwapStart = posSwapStart;
    for (int i = negCount; i < posSwapStart; ++i)
    {
        if (arr[i] > 0)
        {
            posToPosSwapStart++;
        }
    }

    int negIndex = 0;
    int posIndex = negCount;
    int negSwapIndex = negSwapStart;
    int negToPosSwapIndex = posSwapStart;
    int posToPosSwapIndex = posToPosSwapStart;
    bool negJustMoved = false;
    int negMovedFromPos = 0;
    bool posJustMoved = false;
    int posMovedFromPos = 0;

    while (posIndex < n && negIndex < negCount)
    {
        printArr(arr, n);
        std::cout << "negIndex: " << negIndex << std::endl;
        std::cout << "posIndex: " << posIndex << std::endl;
        std::cout << "posSwapStart: " << posSwapStart << std::endl;
        std::cout << "negSwapIndex: " << negSwapIndex << std::endl;
        std::cout << "negToPosSwapIndex: " << negToPosSwapIndex << std::endl;
        std::cout << "posToPosSwapIndex: " << posToPosSwapIndex << std::endl;
        std::cout << "negJustMoved: " << negJustMoved << std::endl;
        std::cout << "posJustMoved: " << posJustMoved << std::endl;
        std::cout << "posMovedFromPos: " << posMovedFromPos << std::endl;
        if (negIndex == negSwapStart)
        {
            negIndex = negSwapIndex;
        }

        if (posIndex == posSwapStart)
        {
            posIndex = negToPosSwapIndex;
        }

        if (posIndex == posToPosSwapStart)
        {
            posIndex = posToPosSwapIndex;
        }

        if (arr[negIndex] < 0)
        {
            if (negIndex < negSwapStart && negJustMoved)
            {
                std::swap(arr[negIndex], arr[negSwapIndex++]);
                negJustMoved = false;
            }
            else
            {
                negIndex++;
            }
        }
        else
        {
            if (posJustMoved)
            {
                if (posMovedFromPos >= posSwapStart)
                {
                    std::swap(arr[negIndex], arr[posToPosSwapIndex++]);
                    posMovedFromPos = posToPosSwapIndex-1;
                }
                else
                {
                    std::swap(arr[negIndex], arr[negToPosSwapIndex++]);
                    posMovedFromPos = negToPosSwapIndex-1;
                }
                if (arr[negIndex] < 0)
                {
                    negJustMoved = true;
                    posJustMoved = false;
                }
                else
                {
                    posJustMoved = true;
                    negJustMoved = false;
                }
                continue;
            }

            if (arr[posIndex] < 0)
            {
                negJustMoved = true;
                posJustMoved = false;
            }
            else
            {
                posJustMoved = true;
                posMovedFromPos = posIndex;
                negJustMoved = false;
            }
            std::swap(arr[negIndex], arr[posIndex++]);
        }
    }
}


int main()
{
    int arr[] = { -1, 1, 3, -2, 2, 5, -3, -2, 6, 10, 18, -5, 20, 3, -6 };

    int size = sizeof(arr) / sizeof(int);

    SpecialSort(arr, size);

    printArr(arr, size);

}

