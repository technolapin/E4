test = {
  'name': 'random_search',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.random.seed(42);
          >>> 
          >>> x = np.random.rand(20);
          >>> y = 0.5*x + 2 + 0.05 * np.random.randn(20);
          >>> w = np.array([0,0]);
          >>> 
          >>> cost = lambda w: np.sum((w[0]*x + w[1] - y)**2);
          >>> alpha  = 0.1;
          >>> epochs = 30;
          >>> draws  = 10;
          >>> 
          >>> w, _ = random_search(w, cost, draws, alpha, epochs);
          >>> 
          >>> print(w)
          122e62316a9030ff898aca00a9a122ca
          # locked
          """,
          'hidden': False,
          'locked': True
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
