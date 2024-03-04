#include "menu.h"

bool IsContinue(bool overrideFlag) {
	if (overrideFlag) {
		return false;
	}
	else {
		char d;
		string strInp;
		bool isOk = false;
		do {
			cout << "����������? (Y/N): ";
			getline(cin, strInp);
			if (regex_match(strInp, kRxYn)) {
				isOk = true;
				d = strInp[0];
				switch (d) {
				case 'Y':
				case 'y':
					return true;
				case 'N':
				case 'n':
					return false;
				}
			}
			else {
				isOk = false;
				cout << "������������ ����!\n";
			}
		} while (!isOk);
	}
}

void PrintMenu() {
	cout << kDelimeter << '\n';
	for (int i = 0; i <= MENU_ITEMS_MAX; i++) {
		cout << std::setw(3) << i << ": " << kMenuItemsArr[i] << '\n';
	}
	cout << kDelimeter << '\n';
}

bool GetInputInt(int& iInp, int min, int max, int forbidden) {
	string strInp;
	bool res;
	getline(cin, strInp);
	if (regex_match(strInp, kRxNumber)) {
		iInp = stoi(strInp);
		if (IS_IN_RANGE(iInp, min, max)) {
			if (forbidden == INT_MAX) {
				res = true;
			}
			else {
				if (iInp != forbidden) {
					res = true;
				}
				else {
					res = false;
				}
			}
			
		}
		else {
			res = false;
		}
	}
	else {
		res = false;
	}
	if (res) {
		return true;
	}
	else {
		cout << "������������ ����!\n";
		return false;
	}
}


MyGraph GenGraph() {
	int vertCnt;
	do {
		cout << "������� ���������� ������ ����� n (" << VERT_CNT_MIN << " <= n <= " << VERT_CNT_MAX << "):\n";
	} while (!GetInputInt(vertCnt, VERT_CNT_MIN, VERT_CNT_MAX));
	cout << '\n';

	MyGraph graph(vertCnt);

	cout << "������� ��������� ������:\n";
	PrintMatrix(graph.GetAdjMatrix());
	cout << '\n';

	return graph;
}

void ExecShimbell(const MyGraph& graph) {
	int edgesCnt, mType;
	do {
		cout << "������� ���������� �����:\n";
	} while (!GetInputInt(edgesCnt, 1, graph.GetVertexCount() - 1));
	cout << '\n';
	do {
		cout << "�������� ���������� � �������:\n������� ���������� ��������� (0), ������� ���������� ��������� (1)\n";
	} while (!GetInputInt(mType, 0, 1));
	cout << '\n';
	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kPositive));
	cout << '\n';
	cout << "������� ��������:\n";
	PrintMatrix(graph.CalcShimbell(edgesCnt, static_cast<ShimbellMode>(mType)));
	cout << '\n';
}

void ExecReachability(const MyGraph& graph) {
	int vert1, vert2;
	iMx reachMatrix = graph.GetReachMatrix();
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert1, 1, graph.GetVertexCount()));
	cout << '\n';
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert2, 1, graph.GetVertexCount()));
	cout << '\n';
	vert1--;
	vert2--;
	cout << "������� ������������:\n";
	PrintMatrix(reachMatrix);
	cout << '\n';
	if (reachMatrix[vert1][vert2]/* != 0*/) {
		cout << "C��������� " << reachMatrix[vert1][vert2] << " ��������� ����� ������� ���������!\n";
	}
	else {
		cout << "�� ���������� ��������� ����� ������� ���������!\n";
	}
	cout << '\n';
}

void ExecDijkstra(const MyGraph& graph) {
	int inpVert, counter = 0;

	do {
		cout << "������� �������� �������:\n";;
	} while (!GetInputInt(inpVert, 1, graph.GetVertexCount()));
	cout << '\n';
	inpVert--;

	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kPositive));
	cout << '\n';

	cout << "� � � � � � �:\n";

	vector<int> distances = graph.Dijkstra(inpVert, counter);
	iMx paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(WeightsType::kModifiedPos));

	for (int i = 0; i < graph.GetVertexCount(); i++) {
		if (i != inpVert) {
			if (paths[i][0] != INF) {
				cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
				for (int j = paths[i].size() - 1; j > 0; j--) {
					cout << std::setw(2) << paths[i][j] + 1 << " -> ";
				}
				cout << std::setw(2) << paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������: " << counter << '\n';
	cout << '\n';

	cout << "� � � � � � �:\n";

	distances = graph.Dijkstra_queue(inpVert, counter);
	paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(WeightsType::kModifiedPos));

	for (int i = 0; i < graph.GetVertexCount(); i++) {
		if (i != inpVert) {
			if (paths[i][0] != INF) {
				cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
				for (int j = paths[i].size() - 1; j > 0; j--) {
					cout << std::setw(2) << paths[i][j] + 1 << " -> ";
				}
				cout << std::setw(2) << paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������: " << counter << '\n';
	cout << '\n';

	//cout << "� �:\n";

	//distances = graph.BellmanFord(inpVert, counter);
	//paths = graph.RestorePaths(inpVert, distances);

	//for (int i = 0; i < graph.GetVertexCount(); i++) {
	//	if (i != inpVert) {
	//		if (paths[i][0] != INF) {
	//			cout << "���������� ���� ������ " << std::setw(2) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
	//			for (int j = paths[i].size() - 1; j > 0; j--) {
	//				cout << std::setw(2) << paths[i][j] + 1 << " -> ";
	//			}
	//			cout << std::setw(2) << paths[i][0] + 1 << '\n';
	//		}
	//		else {
	//			cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
	//		}
	//	}
	//}
	//cout << '\n';
	//cout << "���������� ��������:" << std::setw(4) << counter << '\n';
	//cout<< '\n';
}

void ExecBellmanFord(const MyGraph& graph) {
	int inpVert, counter = 0;

	do {
		cout << "������� �������� �������:\n";;
	} while (!GetInputInt(inpVert, 1, graph.GetVertexCount()));
	cout << '\n';
	inpVert--;

	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kMixed));
	cout << '\n';

	vector<int> distances = graph.BellmanFord(inpVert, graph.GetWeightsMatrix(WeightsType::kMixed), counter);
	iMx paths = graph.RestorePaths(inpVert, distances, graph.GetWeightsMatrix(WeightsType::kModifiedMixed));

	for (int i = 0; i < graph.GetVertexCount(); i++) {
		if (i != inpVert) {
			if (paths[i][0] != INF) {
				cout << "���������� ���� ������ " << std::setw(3) << distances[i] << " �� ������� " << std::setw(2) << i + 1 << ": ";
				for (int j = paths[i].size() - 1; j > 0; j--) {
					cout << std::setw(2) << paths[i][j] + 1 << " -> ";
				}
				cout << std::setw(2) << paths[i][0] + 1 << '\n';
			}
			else {
				cout << "�� ������� " << std::setw(2) << i + 1 << " ���� ���!\n";
			}
		}
	}
	cout << '\n';
	cout << "���������� ��������: " << counter << '\n';
	cout << '\n';
}

void ExecFloydWarshall(const MyGraph& graph) {
	int counter = 0;

	cout << "������� �����:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kMixed));
	cout << '\n';

	iMx distancesMx = graph.FloydWarshall(counter);

	cout << "������� ����������:\n";
	for (int i = 0; i < graph.GetVertexCount(); i++) {
		for (int j = 0; j < graph.GetVertexCount(); j++) {
			if (distancesMx[i][j] != INF) {
				cout << std::setw(3) << distancesMx[i][j] << " ";
			}
			else {
				cout << std::setw(3) << "INF" << " ";
			}
		}
		cout << '\n';
	}
	cout << '\n';

	cout << "���������� ��������: " << counter << '\n';
	cout << '\n';
}

void ExecMinCostFlow(const MyGraph& graph) {
	int vert1, vert2;
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert1, 1, graph.GetVertexCount()));
	cout << '\n';
	do {
		cout << "������� ����� ������ �������:\n";
	} while (!GetInputInt(vert2, 1, graph.GetVertexCount(), vert1));
	cout << '\n';
	vert1--;
	vert2--;

	cout << "������� ���������� ������������:\n";
	PrintMatrix(graph.GetMaxFlowMatrix());
	cout << '\n';

	int maxFlow = graph.fordFulkerson(vert1, vert2);
	cout << "������������ �����: " << maxFlow << '\n';
	cout << "������������ �����: " << maxFlow * 2 / 3 << '\n';
	cout << '\n';

	cout << "������� ����������:\n";
	PrintMatrix(graph.GetWeightsMatrix(WeightsType::kModifiedMixed));
	cout << '\n';

	McfRetVals retVals;
	int mcf = graph.�alcMinCostFlow(vert1, vert2, (maxFlow * 2 / 3), retVals);

	cout << "������� �������:\n";
	PrintMatrix(retVals.modFlowMx);
	cout << '\n';

	cout << "������� ���������� �� ������� ������:\n";
	PrintMatrix(retVals.modCostMx);
	cout << '\n';

	int resCnt = retVals.flows.size();
	for (int k = 0; k < resCnt; k++) {
		cout << "����� �������� " << retVals.flows[k] << " �� ���������� " << retVals.costsPerPath[k] << " �� ������� ������\n";
		cout << "�� ����: ";
		for (int i = retVals.paths[k].size() - 1; i > 0; i--) {
			cout << retVals.paths[k][i] + 1 << " -> ";
		}
		cout << retVals.paths[k][0] + 1;
		cout << '\n';
		cout << "�������� ���������: " << retVals.flows[k] * retVals.costsPerPath[k] << '\n';
		cout << '\n';
	}

	cout << "�������� ������ ����������� ���������: " << mcf << '\n';
	cout << '\n';
}

void ExecKruskal(const MyGraph& graph) {
	int counter = 0, sum = 0;
	iMx minSpanTree = graph.Kruskal(graph.GetWeightsMatrix(WeightsType::kPositive), &counter, &sum);

	cout << "������� ����� ����������� ������:\n";
	PrintMatrix(minSpanTree);
	cout << '\n';

	cout << "��� ����������� ������: " << sum << '\n';
	cout << '\n';

	cout << "���������� ��������: " << counter << '\n';
	cout << '\n';
}

void ExecPrim(const MyGraph& graph) {
	int counter = 0, sum = 0;
	iMx minSpanTree = graph.Prim(graph.GetWeightsMatrix(WeightsType::kPositive), &counter, &sum);

	cout << "������� ����� ����������� ������:\n";
	PrintMatrix(minSpanTree);
	cout << '\n';

	cout << "��� ����������� ������: " << sum << '\n';
	cout << '\n';

	cout << "���������� ��������: " << counter << '\n';
	cout << '\n';
}

void ExecSpanTreesCnt(const MyGraph& graph) {
	cout << "������� ��������:\n";
	PrintMatrix(graph.GenKirchhoff());
	cout << '\n';

	cout << "���������� �������� �������� � �����: " << graph.CalcSpanTreesCnt() << '\n';
	cout << '\n';
}

void ExecPrufer(const MyGraph& graph) {
	iMx weightMx = graph.Kruskal(graph.GetWeightsMatrix(WeightsType::kPositive));
	iMx decodedMx;
	vector<int> prufCode, prufWeights;

	cout << "������� ����� ����������� ������:\n";
	PrintMatrix(weightMx);
	cout << '\n';
	graph.PruferEncode(weightMx, prufCode, prufWeights);

	cout << "��� �������:\n";
	//if (weightMx.size() > 2) {
		for (int i = 0; i < prufCode.size(); i++) {
			cout << prufCode[i] << ' ';
		}
	/* }
	else {
		cout << "��� ������� ��� ������, ���������� �� ���� ����, �����������.\n";
	}*/
	cout << '\n';

	cout << "���� ����:\n";
	for (int i = 0; i < prufWeights.size(); i++) {
		cout << prufWeights[i] << ' ';
	}
	cout << '\n';

	decodedMx = graph.PruferDecode(prufCode, prufWeights);
	cout << "\n��������������� ������� ����� ����������� ������:\n";
	PrintMatrix(decodedMx);
	cout << '\n';

	if (decodedMx == weightMx) {
		cout << "������������� �����.\n";
	}
	else {
		cout << "������������� �������.\n";
	}

	cout << '\n';
}

void ExecEulerCycle(const MyGraph& graph) {
	IsEulerOrHamilton res;
	iMx resWeightMx;
	vector<int> eulerPath = graph.EulerCycles(graph.GetWeightsMatrix(WeightsType::kPositive), resWeightMx, res);

	switch (res) {
	case IsEulerOrHamilton::kFalse2Vert:
		cout << "���� �� ���� ������ �� ����� ������� ����!\n";
		break;
	case IsEulerOrHamilton::kFalseUnmodifiable:
		/*cout << "���� �� �������� ���������. ������������� �� �������� ����� ����������.\n";
		break;*/
	case IsEulerOrHamilton::kFalseModifiable:
		cout << "���� �� �������� ���������. ��������������� �� �������� ����� ��������.\n\n";
	case IsEulerOrHamilton::kTrue:
		cout << "������� ������� �������� �����:\n";
		PrintMatrix(resWeightMx);
		cout << '\n';
		cout << "������� ����:\n";
		for (int i = 0; i < eulerPath.size() - 1; i++) {
			cout << eulerPath[i] + 1 << " -> ";
		}
		cout << eulerPath[eulerPath.size() - 1] + 1 << '\n';
		break;
	default:
		break;
	}
	cout << '\n';
}

void ExecHamiltonCycle(const MyGraph& graph) {
	IsEulerOrHamilton res;
	iMx resWeightMx;
	int minLen;
	vector<int> minPath = graph.Hamilton(graph.GetWeightsMatrix(WeightsType::kPositive), resWeightMx, res, minLen);

	switch (res) {
	case IsEulerOrHamilton::kFalse2Vert:
		cout << "���� �� ���� ������ �� ����� ����������� ����!\n";
		break;
	case IsEulerOrHamilton::kFalseModifiable:
		cout << "���� �� �������� �������������. ��������������� �� ������������ ����� ��������.\n\n";
	case IsEulerOrHamilton::kTrue:
		cout << "������� ������� ������������ �����:\n";
		PrintMatrix(resWeightMx);
		cout << '\n';
		cout << "����������� ����������� ����:\n";
		for (int i = 0; i < minPath.size() - 1; i++) {
			cout << minPath[i] + 1 << " -> ";
		}
		cout << minPath[minPath.size() - 1] + 1 << '\n';
		cout << "��� ����: " << minLen << '\n';
		break;
	default:
		break;
	}
	cout << '\n';
}