test = {
  'name': 'circular_sampling',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> np.random.seed(0);
          >>> 
          >>> directions = circular_sampling(2, 5);
          >>> 
          >>> print(directions)
          [[ 0.97522402  0.22121958]
           [ 0.40025144  0.91640536]
           [ 0.88601999 -0.46364704]
           [ 0.98754693 -0.15732467]
           [-0.24380083  0.96982532]]
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
