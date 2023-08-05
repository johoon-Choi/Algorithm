#include <iostream>
#define N 55

using namespace std;

int n;
int arr[N];

void solve() {
	int sum = arr[0];
	bool canMul = true;

	for (int i = 1; i < n; i++) {
		if (!canMul) {
			sum += arr[i];
			canMul = true;
		}
		else if (0 < arr[i]) {		// 현재 숫자가 양수인 경우
			if (0 < arr[i - 1]) {

			}
		}
		else if (arr[i] < 0) {		// 현재 숫자가 음수인 경우
			if (0 < arr[i - 1]) {

			}
			else if (arr[i - 1] < 0) {
				sum += arr[i - 1] * arr[i];
				canMul = false;
			}
			else {
				// 0 * arr[i]
				canMul = false;
			}
		}
		else {						// 현재 숫자가 0인 경우
			// nothing...
		}
	}
}

int solve2(int idx, int bef, int sum, bool canMul) {
	if (1 < bef) {
		if (canMul) {

		}
		else {

		}
	}
	else if (bef == 1) {
		if (canMul) {

		}
		else {

		}

	}
	else if (!bef) {
		if (canMul) {

		}
		else {

		}

	}
	else if (bef == -1) {
		if (canMul) {

		}
		else {

		}

	}
	else if (bef < -1) {
		if (canMul) {

		}
		else {

		}

	}

	if (idx < n - 1)
		return solve2(idx + 1, arr[idx], sum, canMul);
	else return sum;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	cout << solve2(1, arr[0], 0, true);
}