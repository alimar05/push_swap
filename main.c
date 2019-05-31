#include <stdio.h>

int		max(int *arr, int l, int r)
{
	int		u;
	int		v;
	int		m;

	m = (l + r) >> 1;
	if (l == r)
		return (arr[l]);
	u = max(arr, l, m);
	v = max(arr, m + 1, r);
	return (u > v ? u : v);
}

int		main(void)
{
	int		arr[] = {3, 5, 1, 7, 9, 2, 4, 6};

	printf("%d\n", max(arr, 0, 7));
	return (0);
}
