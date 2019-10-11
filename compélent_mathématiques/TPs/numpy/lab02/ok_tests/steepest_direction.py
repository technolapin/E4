test = {
  'name': 'steepest_direction',
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
          >>> alpha = 0.1;
          >>> directions = circular_sampling(2, 5);
          >>> 
          >>> descent = steepest_direction(w, cost, directions, alpha);
          >>> 
          >>> print(descent)
          25ee2ea728ec1f3579778d5ad97e2e4b
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
