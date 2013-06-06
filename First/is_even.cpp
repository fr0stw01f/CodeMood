struct is_even
{
	bool operator()(int x) {
		return x%2 == 0;
	}
};
