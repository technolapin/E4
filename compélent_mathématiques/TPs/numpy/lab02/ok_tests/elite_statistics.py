test = {
  'name': 'elite_statistics',
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
          >>> cost = lambda w: np.sum((w[0]*x + w[1] - y)**2);
          >>> 
          >>> samples = np.random.rand(10, 2);
          >>> costs = np.array([cost(w) for w in samples]);
          >>> 
          >>> mean, std = elite_statistics(samples, costs, n_elites = 3);
          >>> 
          >>> print(mean, std)
          cc19cc6cf366c39e927b96d7b5d11205
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
