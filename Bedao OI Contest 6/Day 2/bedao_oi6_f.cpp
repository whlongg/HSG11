#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef int64_t ll;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to compute extended gcd and find x and y such that a*x + b*y = gcd(a, b)
ll extended_gcd(ll a, ll b, ll &x, ll &y) {
    if (a == 0) { x = 0; y = 1; return b; }
    ll x1, y1;
    ll d = extended_gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

// Function to compute modular inverse of a modulo m
ll mod_inverse(ll a, ll m) {
    ll x, y;
    ll g = extended_gcd(a, m, x, y);
    if (g != 1) return -1; // Inverse doesn't exist
    x = (x % m + m) % m;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, M, L, C;
    cin >> N >> M >> L >> C;
    vector<ll> A(N), B(M);
    for (ll& a : A) cin >> a;
    for (ll& b : B) cin >> b;
    ll Q;
    cin >> Q;
    vector<ll> V(Q), T(Q);
    for (ll i = 0; i < Q; ++i) {
        cin >> V[i] >> T[i];
        --V[i]; // 0-based indexing
    }

    // Precompute gcd(C, L), lcm(C, L)
    ll g = gcd(C, L);
    ll C_g = C / g;
    ll L_g = L / g;
    ll lcm = (C / g) * L; // C and L may be large, careful with overflow

    // Precompute modular inverses for C' modulo L'
    ll inv_C = mod_inverse(C_g % L_g, L_g);
    if (inv_C == -1) inv_C = 0; // Should not happen since C_g and L_g are co-prime

    // Process each query
    for (ll q = 0; q < Q; ++q) {
        ll idx = V[q];
        ll T_i = T[q];
        ll A_i = A[idx];

        ll total_picks = 0;

        for (ll j = 0; j < M; ++j) {
            ll B_j = B[j];
            ll t0 = (B_j - A_i + L) % L;
            if (t0 % g != 0) continue;
            ll t0_g = t0 / g;

            // Solve C_g * s ≡ t0_g mod L_g
            ll s = (inv_C * t0_g) % L_g;

            ll t_start = s * C;
            if (t_start > T_i) continue;

            ll num_picks = (T_i - t_start) / lcm + 1;
            total_picks += num_picks;
        }
        cout << total_picks << '\n';
    }

    return 0;
}