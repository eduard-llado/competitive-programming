
// all with leading digits first (in index zero)

vector<int> get_rep(ll x) {
   vector<int> ans;
   while (x) {
      ans.push_back(x % 10);
      x /= 10;
   }
   reverse(all(ans));
   return ans;
}

bool compare(vector<int> x, vector<int> y) {
   if (x.size() != y.size())
      return x.size() < y.size();
   for (int i = 0; i < (int)x.size(); ++i)
      if (x[i] < y[i])
         return true;
      else if (x[i] > y[i])
         return false;
   return false;
}

vector<int> add(vector<int> x, vector<int> y) {
   if (x.size() > y.size())
      swap(x, y);
   reverse(all(x));
   reverse(all(y));
   vector<int> ans;
   int i = 0, carry = 0;
   while (i < (int)y.size()) {
      if (i < (int)x.size()) {
         ans.push_back((x[i] + y[i] + carry) % 10);
         carry = (x[i] + y[i] + carry) / 10;
      }
      else {
         ans.push_back((y[i] + carry) % 10);
         carry = (y[i] + carry) / 10;         
      }
      ++i;
   }
   if (carry)
      ans.push_back(carry);
   reverse(all(ans));
   return ans;
}