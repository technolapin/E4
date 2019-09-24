test = {
  'name': 'kmeans_cost',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> X, y = datasets.make_blobs(n_samples=30, random_state=42);
          >>> c_True = np.stack([np.mean(X[y==i], axis=0) for i in range(3)], axis=0);
          >>> 
          >>> kmeans_cost(c_True, X)
          5503262241207018c845188f0c0348ed
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
