#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------------------------------------

template<typename A, typename B> ostream &operator<<(ostream &os, const pair<A, B> &p) 
{
	return os << "(" << p.first << ", " << p.second << ")";
}

template<typename A, typename B, typename C> ostream &operator<<(ostream &os, const tuple<A, B, C> &t) 
{
	return os << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ")";
}

template<typename A, typename B, typename C, typename D> ostream &operator<<(ostream &os, const tuple<A, B, C, D> &t)
{
	return os << "(" << get<0>(t) << ", " << get<1>(t) << ", " << get<2>(t) << ", " << get<3>(t) << ")";
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type >::type> ostream &operator<<(ostream &os, const T_container &v)
{
	os << '{';
	string sep;
	for(const T &x: v) 
		os << sep << x, sep = ", ";
	return os << '}';
}

// ------------------------------------------------------------------------------------

template<typename T> void debug_out(string s, T t)
{
	cout << "[" << s << ": " << t << "]\n";
}

template<typename T, typename...U> void debug_out(string s, T t, U...u)
{
	int w = 0, c = 0;
	while(w < (int) s.size())
	{
		if(s[w] == '(' or s[w] == '{' or s[w] == '[') c++;
		if(s[w] == ')' or s[w] == '}' or s[w] == ']') c--;
		if(!c and s[w] == ',') break;
		w++;
	}
	cout << "[" << s.substr(0, w) << ": " << t << "] ";
	debug_out(s.substr(w + 2, (int) s.size() - w - 1), u...);
}

// ------------------------------------------------------------------------------------

template<typename T> string bin(T x)
{
	if(x == T(0))
		return "0";
    string res = "";
    while(x)
    {
        res += char('0' + (x & 1));
        x /= 2;
    }
    reverse(res.begin(), res.end());
    return res;
}

// ------------------------------------------------------------------------------------

#define dbg(Z...) debug_out(#Z, Z)