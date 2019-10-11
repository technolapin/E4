test = {
  'name': 'grid_search',
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
          >>> w = np.array([1.,1.]);
          >>> 
          >>> cost  = lambda w: np.sum((w[0]*x + w[1] - y)**2);
          >>> w_min = [0,1];
          >>> w_max = [1,3];
          >>> 
          >>> w, _ = grid_search(cost, w_min, w_max);
          >>> 
          >>> print(w)
          5d482b573553c57d0252d8cba681dde9
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
