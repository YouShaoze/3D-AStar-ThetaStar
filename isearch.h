#ifndef ISEARCH_H
#define ISEARCH_H
#include "list.h"
#include "map.h"
#include "ilogger.h"
#include "searchresult.h"
#include "environmentoptions.h"
#include <unordered_set>
#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <chrono>
class ISearch
{
    public:
        ISearch();
        virtual ~ISearch(void);

        SearchResult startSearch(ILogger *Logger, const Map &Map, const EnvironmentOptions &options);
        Node findMin(int size);
        double MoveCost(int start_i, int start_j, int fin_i, int fin_j, const EnvironmentOptions &options);

    protected:
        virtual void addOpen(Node newNode) = 0; //������ ����� �� ������ ��������� ������� � ������ OPEN
        virtual double computeHFromCellToCell(int start_i, int start_j, int fin_i, int fin_j, const EnvironmentOptions &options) = 0; //��� �������� � BFS ���� ����� ������ ���������� ����
        virtual std::list<Node> findSuccessors(Node curNode, const Map &map, const EnvironmentOptions &options);//�����, ������� ���� ������� ������� �������, ��������������� ���������� ������
        virtual void makePrimaryPath(Node curNode);//������ ���� �� ������� �� ��������
        virtual void makeSecondaryPath(const Map &map, Node curNode);//��������� ��������� ���� �� ������, ���������� ������ ������ �������
        virtual Node resetParent(Node current, Node parent, const Map &map, const EnvironmentOptions &options) { return current;}//������ ��������, ����� ��� ��������� Theta*
        virtual bool stopCriterion();
        SearchResult    sresult; //��������� ������
        NodeList         lppath, hppath; //������ OPEN, CLOSE � ����
        Node lastnode;
        std::unordered_set<Node> close;
        NodeList *open;
        int     openSize;
        int     sizelimit; //����������� �� ������ OPEN
        float   hweight; //��� ���������
        int     breakingties; //�������� ������ ��������� ������� �� OPEN, ����� F-�������� �����

};
#endif
