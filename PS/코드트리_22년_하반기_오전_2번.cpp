#include <iostream>
#include <unordered_map>

using namespace std;

int q, n, m;

struct Box {
	int r_id;
	int weight;
	int belt;
	int flag; // 하차 유무
	Box* prev;
	Box* next;
};

struct Belt {
	Box* start;
	Box* end;
};

Box boxes[100000];
Belt belts[10];
int ids[100000];
int weights[100000];
unordered_map<int, int> ridx2bidx;
bool isBroken[10];

void addBox(int belt, int idx) {
	boxes[idx].r_id = ids[idx];
	boxes[idx].weight = weights[idx];
	boxes[idx].belt = belt;
	if (belts[belt].start == NULL) {
		belts[belt].start = &boxes[idx];
		belts[belt].end = &boxes[idx];
	}
	else {
		boxes[idx].prev = belts[belt].end;
		belts[belt].end->next = &boxes[idx];
		belts[belt].end = &boxes[idx];
	}
	ridx2bidx.insert({boxes[idx].r_id, idx});
}

void init() {
	int query;
	cin >> query >> n >> m;
	for (int i = 0; i < n; ++i) cin >> ids[i];
	for (int i = 0; i < n; ++i) cin >> weights[i];
	int s = n / m;
	for (int belt = 0; belt < m; ++belt) {
		for (int i = s * belt; i < s * (belt + 1); ++i) {
			addBox(belt, i);
		}
	}
}

int f_200(int w_max) {
	int ret = 0;
	for (int belt = 0; belt < m; ++belt) {
		if (isBroken[belt]) continue;
		if (belts[belt].start == NULL) continue;
		if (belts[belt].start->weight <= w_max) {
			// 하차
			ret += belts[belt].start->weight;
			belts[belt].start->flag = true;
			if (belts[belt].start->next == NULL) {
				belts[belt].start = NULL;
				belts[belt].end = NULL;
			}
			else {
				belts[belt].start->next->prev = NULL;
				belts[belt].start = belts[belt].start->next;
			}
		}
		else {
			// 맨 뒤로 보내기
			if (belts[belt].start->next != NULL) {
				Box* tmp = belts[belt].start;
				belts[belt].start->next->prev = NULL;
				belts[belt].start = belts[belt].start->next;
				tmp->next = NULL;
				belts[belt].end->next = tmp;
				tmp->prev = belts[belt].end;
				belts[belt].end = tmp;
			}
		}
	}
	return ret;
}

int f_300(int r_id) {
	if (ridx2bidx.find(r_id) == ridx2bidx.end()) return -1;
	if (boxes[ridx2bidx[r_id]].flag) return -1;
	else {
		int b_id = ridx2bidx[r_id];
		boxes[b_id].flag = true;
		if (boxes[b_id].prev == NULL && boxes[b_id].next != NULL) {
			// 첫번째 상자를 제거하는 경우
			boxes[b_id].next->prev = NULL;
			belts[boxes[b_id].belt].start = boxes[b_id].next;
		}
		else if (boxes[b_id].prev != NULL && boxes[b_id].next == NULL) {
			// 마지막 상자를 제거하는 경우
			boxes[b_id].prev->next = NULL;
			belts[boxes[b_id].belt].end = boxes[b_id].prev;
		}
		else if (boxes[b_id].prev != NULL && boxes[b_id].next != NULL) {
			boxes[b_id].prev->next = boxes[b_id].next;
			boxes[b_id].next->prev = boxes[b_id].prev;
		}
		else {
			belts[boxes[b_id].belt].start = NULL;
			belts[boxes[b_id].belt].end = NULL;
		}
	}
	return r_id;
}

int f_400(int f_id) {
	if (ridx2bidx.find(f_id) == ridx2bidx.end()) return -1;
	int b_id = ridx2bidx[f_id];
	if (boxes[b_id].flag) return -1;
	if (boxes[b_id].prev == NULL) {
		return boxes[b_id].belt+1;
	}
	int belt = boxes[b_id].belt;
	belts[belt].start->prev = belts[belt].end;
	belts[belt].end->next = belts[belt].start;
	boxes[b_id].prev->next = NULL;
	belts[belt].start = &boxes[b_id];
	belts[belt].end = boxes[b_id].prev;
	boxes[b_id].prev = NULL;
	return belt+1;
}

int f_500(int b_num) {
	b_num -= 1;
	if (isBroken[b_num]) return -1;
	isBroken[b_num] = true;
	if (belts[b_num].start == NULL && belts[b_num].end == NULL) return b_num + 1;
	int nxt;
	for (int i = 1; i < m; ++i) {
		nxt = (b_num + i) % m;
		if (!isBroken[nxt]) {
			if (belts[nxt].start==NULL && belts[nxt].end == NULL) {
				belts[nxt].start = belts[b_num].start;
				belts[nxt].end = belts[b_num].end;
			}
			else {
				belts[nxt].end->next = belts[b_num].start;
				belts[b_num].start->prev = belts[nxt].end;
				belts[nxt].end = belts[b_num].end;
			}
			break;
		}
	}
	Box* box = belts[b_num].start;
	while (box !=NULL) {
		box->belt = nxt;
		box = box->next;
	}
	return b_num + 1;
}

int main() {
	// freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	cin >> q;
	init();
	for (int i = 1; i < q; ++i) {
		int q_num, x, ret;
		cin >> q_num >> x;
		if (q_num == 200) ret = f_200(x);
		else if (q_num == 300) ret = f_300(x);
		else if (q_num == 400) ret = f_400(x);
		else ret = f_500(x);
		cout << ret << '\n';
	}
}