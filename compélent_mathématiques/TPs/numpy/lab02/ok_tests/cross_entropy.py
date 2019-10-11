test = {
  'name': 'cross_entropy',
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
          >>> 
          >>> draws  = 50;
          >>> alpha  = 0.1;
          >>> epochs = 100;
          >>> 
          >>> w, _ = cross_entropy_search(w, cost, draws, alpha, epochs);
          >>> 
          >>> print(w)
          5d5f21b5f66af10dacf57afe66cbc682
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
